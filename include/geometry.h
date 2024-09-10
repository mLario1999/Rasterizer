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

struct Vec3d {
    double x;
    double y;
    double z;
    Vec3d() : x(0), y(0), z(0) {}
    Vec3d(double x, double y, double z) : x(x), y(y), z(z) {}
    Vec3d operator+(const Vec3d& other) const {
        return Vec3d(x+other.x, y+other.y, z+other.z);
    }
    Vec3d operator-(const Vec3d& other) const {
        return Vec3d(x-other.x, y-other.y, z-other.z);
    }
    Vec3d operator*(const int scalar) const {
        return Vec3d(x*scalar, y*scalar, z*scalar);
    }
    Vec3d operator/(const int scalar) const {
        return Vec3d(x/scalar, y/scalar, z/scalar);
    }
};

#endif //__GEOMETRY_H__