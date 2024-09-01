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
        float t = (x - p1.x) / (p2.x - p1.x);
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

void tgabasic::drawTriangle(Vec2d a, Vec2d b, Vec2d c, TGAImage &image, const TGAColor color, const RASMETHOD methods)
{
    double area = edgeFunc(a, b, c);
    if (area < 0 && (methods & CULL)) return; // triangle is backwards facing

    if (methods & WIRE) {
        drawLine(a, b, image, color);
        drawLine(b, c, image, color);
        drawLine(c, a, image, color);
    } 
    if (methods & FILL) {
        if (area < 0) std::swap(b, c);
        std::array<Vec2d, 2> bounding_box = getBoundingBox(a, b, c);
        Vec2d lower = bounding_box[0];
        Vec2d upper = bounding_box[1];
        Vec2d p;
        // Loop through the bounding box
        for (p.x = lower.x; p.x <= upper.x; p.x++) {
            for (p.y = lower.y; p.y <= upper.y; p.y++) {

                // Calculate edge function values
                double ABP = edgeFunc(a, b, p);
                double BCP = edgeFunc(b, c, p);
                double CAP = edgeFunc(c, a, p);

                // Check if the point is inside the triangle
                if ((ABP >= 0 && BCP >= 0 && CAP >= 0)) {
                    image.setPixel(p.x, p.y, color); // Ensure integer pixel access
                }
            }
        }
    }
}

