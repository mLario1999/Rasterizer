#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#pragma once

struct Vec2d {
    double x;
    double y;
    Vec2d() : x(0), y(0) {}
    Vec2d(double x, double y) : x(x), y(y) {}
    Vec2d operator+(const Vec2d& other) const {
        return Vec2d(x+other.x, y+other.y);
    }
    Vec2d operator-(const Vec2d& other) const {
        return Vec2d(x-other.x, y-other.y);
    }
    Vec2d operator*(const int scalar) const {
        return Vec2d(x*scalar, y*scalar);
    }
    Vec2d operator/(const int scalar) const {
        return Vec2d(x/scalar, y/scalar);
    }
};

#endif //__GEOMETRY_H__