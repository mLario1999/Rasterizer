#include "tgabasic.h"

using namespace tgabasic;

int main() {
    TGAColor red = TGAColor(255, 0, 0, 255);  // Red color
    TGAColor greenish = TGAColor(28, 234, 67, 0.8);
    TGAImage image(100, 100, 3);  // Create a 100x100 image with RGB (3 bytes per pixel)
    image.setPixel(52, 41, red); 
    image.setPixel(52, 42, red);
    image.setPixel(52, 52, greenish);
    image.writeTGAFile("output.tga");  // Write the image to output.tga
}