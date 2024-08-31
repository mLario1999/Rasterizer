#ifndef __TGABASIC__
#define __TGABASIC__

#pragma once

#include <utility>
#include "geometry.h"

namespace tgabasic {

struct Point : public std::pair<int, int> {
    using std::pair<int, int>::pair;
    int& x = this->first;
    int& y = this->second;

};

#pragma pack(push,1)
    typedef struct {
        char  idlength;
        char  colourmaptype;
        char  datatypecode;
        short colourmaporigin;
        short colourmaplength;
        char  colourmapdepth;
        short x_origin;
        short y_origin;
        short width;
        short height;
        char  bitsperpixel;
        char  imagedescriptor;
    } TGAHEADER;
#pragma pack(pop)

    struct TGAColor {
        union {
            struct {
                unsigned char b, g, r, a;
            };
            unsigned char raw[4];
            unsigned int val;
        };
        int bytespp;
        TGAColor() : val(0), bytespp(1) {
        }
        TGAColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : b(B), g(G), r(R), a(A), bytespp(4) {
        }
};

    class TGAImage {
    public:
        TGAImage();
        TGAImage(int width, int height, int bpp);
        bool setPixel(int x, int y, TGAColor c);
        bool writeTGAFile(const char* dst);
    protected:
        unsigned char* data;
        int height;
        int width;
        int bytespp;
    };

    void drawLine(Vec2d p1, Vec2d p2, TGAImage& image, TGAColor c);
    void drawTriangle(Vec2d p1, Vec2d p2, Vec2d p3, TGAImage& image, TGAColor c);
    
}

#endif // __TGABASIC__