#include "tgabasic.h"
#include "geometry.h"
#include <cmath>
#include <algorithm>
#include <array>
#include <iostream>

using namespace tgabasic;

void tgabasic::drawLine(Vec2d p1, Vec2d p2, TGAImage& image, TGAColor color) {
    bool steep = false;
    if (std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y)) { // If the line is steep -> transpose the image
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        steep = true;
    }
    if (p2.x < p1.x) {
        std::swap(p1.x, p2.x);
        std::swap(p1.y, p2.y);
    }
    for (int x = static_cast<int>(p1.x); x <= static_cast<int>(p2.x); x++) {
        double t = (x - p1.x) / (p2.x - p1.x);
        int y = static_cast<int>(p1.y * (1.0f - t) + p2.y * t);
        if (steep) {
            image.setPixel(y, x, color);
        } else {
            image.setPixel(x, y, color);
        }
    }
}

double edgeFunc(Vec2d a, Vec2d b, Vec2d c) {
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x); // Shoelace formula (division omitted)
}

std::array<Vec2d, 2> getBoundingBox(const Vec2d& p1, const Vec2d& p2, const Vec2d& p3) {
    // Calculate minimum and maximum x and y coordinates
    double minX = std::min({p1.x, p2.x, p3.x});
    double minY = std::min({p1.y, p2.y, p3.y});
    double maxX = std::max({p1.x, p2.x, p3.x});
    double maxY = std::max({p1.y, p2.y, p3.y});

    // Create the bounding box
    Vec2d lowerBound(minX, minY);
    Vec2d upperBound(maxX, maxY);

    // Return as std::array
    return {lowerBound, upperBound};
}

void tgabasic::drawTriangle(Vec3d a, Vec3d b, Vec3d c, TGAImage &image, const TGAColor color, const RASMETHOD flags, int* z_buffer)
{
    Vec2d a_2d(a.x, a.y);
    Vec2d b_2d(b.x, b.y);
    Vec2d c_2d(c.x, c.y);
    int height = image.getHeight();
    int width = image.getWidth();
    double area = edgeFunc(a_2d, b_2d, c_2d);
    
    if (area < 0 && (flags & CULL)) return; // Triangle is back-facing and culled

    if (area == 0) return; // Degenerate triangle (line or point), skip

    if (flags & FILL) {
        if (area < 0) {
            std::swap(b, c); 
            std::swap(b_2d, c_2d);
        }
        
        std::array<Vec2d, 2> bounding_box = getBoundingBox(a_2d, b_2d, c_2d);
        Vec2d lower = bounding_box[0];
        Vec2d upper = bounding_box[1];
        Vec2d p;
        
        // Loop through the bounding box
        for (p.x = lower.x; p.x <= upper.x; p.x++) {
            for (p.y = lower.y; p.y <= upper.y; p.y++) {
                // check if the points are inside the image
                if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height) {
                    // Calculate edge function values
                    double ABP = edgeFunc(a_2d, b_2d, p);
                    double BCP = edgeFunc(b_2d, c_2d, p);
                    double CAP = edgeFunc(c_2d, a_2d, p);

                    // Check if the point is inside the triangle
                    if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
                        // calculate weights for z value (barycentric)
                        double w0 = ABP / area;
                        double w1 = BCP / area;
                        double w2 = CAP / area;
                        double p_z = w0 * a.z + w1 * b.z + w2 * c.z; // compute z value
                        int z_index = int(p.x + p.y * width); // find pixel index for z_buffer
                        if (z_buffer[z_index] < p_z) {
                            z_buffer[z_index] = static_cast<int>(p_z);
                            image.setPixel(static_cast<int>(p.x), static_cast<int>(p.y), color);
                        }
                    }
                }
            }
        }
    }
}