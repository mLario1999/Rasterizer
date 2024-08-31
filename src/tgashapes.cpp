#include "tgabasic.h"
#include "geometry.h"
#include <cmath>

using namespace tgabasic;

void tgabasic::drawLine(Vec2d p1, Vec2d p2, TGAImage& image, TGAColor c)
{
    bool steep = false;
    if (std::abs(p1.x-p2.x) < std::abs(p1.y-p2.y)) {
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        steep = true;
    }
    if (p2.x < p1.x) {
        std::swap(p1.x, p2.x);
        std::swap(p1.y, p2.y);
    }
    for (int x = p1.x; x <= p2.x; x++) {
        float t = (x-p1.x)/(float) (p2.x-p1.x);
        int y = p1.y*(1.-t)+p2.y*t;
        if (steep) {
            image.setPixel(y, x, c);
        } else {
            image.setPixel(x, y, c);
        }
    }
}

void tgabasic::drawTriangle(Vec2d p1, Vec2d p2, Vec2d p3, TGAImage &image, TGAColor c)
{
    drawLine(p1, p2, image, c);
    drawLine(p2, p3, image, c);
    drawLine(p3, p1, image, c);
}
