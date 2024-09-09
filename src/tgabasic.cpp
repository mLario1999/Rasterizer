#include "tgabasic.h"
#include <cstring>
#include <fstream>
#include <iostream>

const tgabasic::TGAColor tgabasic::ColorPalette::RED(255, 0, 0, 255);
const tgabasic::TGAColor tgabasic::ColorPalette::GREEN(0, 255, 0, 255);
const tgabasic::TGAColor tgabasic::ColorPalette::BLUE(0, 0, 255, 255);
const tgabasic::TGAColor tgabasic::ColorPalette::WHITE(255, 255, 255, 255);
const tgabasic::TGAColor tgabasic::ColorPalette::BLACK(0, 0, 0, 255);

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

void tgabasic::TGAImage::flipVertically() {
    int start = 0;
    int end = height - 1; 
    int row_size = width * bytespp;

    while (start < end) {
        int start_index = start * row_size;
        int end_index = end * row_size;

        unsigned char* temp = new unsigned char[row_size];

        // Swap the rows
        memcpy(temp, data + start_index, row_size);
        memcpy(data + start_index, data + end_index, row_size);
        memcpy(data + end_index, temp, row_size);

        delete[] temp;

        start++;
        end--;
    }
}

unsigned char *tgabasic::TGAImage::getData()
{
    return data;
}


