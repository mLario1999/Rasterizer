#include "tgabasic.h"

using namespace tgabasic;
int main() {
    TGAColor red(255,0,0,255);
    TGAImage image(1920,1080, 3);
    drawTriangle({20,13}, {40,80}, {50, 13}, image, red);
    image.writeTGAFile("output.tga");
}