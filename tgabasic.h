#ifndef __TGABASIC__
#define __TGABASIC__

#pragma once

namespace tgabasic {

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
}

#endif // __TGABASIC__