#include "tgabasic.h"
#include <cstring>
#include <fstream>
#include <iostream>

tgabasic::TGAImage::TGAImage() 
    : data(nullptr), width(0), height(0), bytespp(0) {}

tgabasic::TGAImage::TGAImage(int w, int h, int bpp)
    : data(NULL), width(w), height(h), bytespp(bpp) 
{
    unsigned long nbytes = width * height * bytespp;
    data = new unsigned char[nbytes];
    memset(data, 0, nbytes);
}

bool tgabasic::TGAImage::setPixel(int x, int y, TGAColor c) {
    if (!data || x < 0 || y < 0 || x >= width || y >= height) {
        return false;
    }
    memcpy(data + (y * width + x) * bytespp, c.raw, bytespp);
    return true;
}

bool tgabasic::TGAImage::writeTGAFile(const char *dst) {
    std::ofstream fOut;
    fOut.open(dst, std::ios::binary);
    if (!fOut.is_open()) {
        std::cerr << "Could not open tga file\n";
        return false;
    }
    TGAHEADER header;
    memset((void*)&header, 0, sizeof(header));
    header.bitsperpixel = bytespp << 3;
    header.width = width;
    header.height = height;
    header.datatypecode = 2; // Uncompressed RGB
    header.imagedescriptor = 0x20; // Top-left origin
    fOut.write((char*)&header, sizeof(header));
    if (!fOut.good()) {
        std::cerr << "Could not write tga header to file\n";
        fOut.close();
        return false;
    }
    fOut.write((char*)data, height * width * bytespp);
    if (!fOut.good()) {
        std::cerr << "Could not write tga data to file\n";
        fOut.close();
        return false;
    }
    return true;
}

