#include "tgabasic.h"

using namespace tgabasic;

int main() {
    TGAImage image(376,238, 3);
    drawTriangle({0, 0}, {3, 0}, {8,8}, image,  ColorPalette::RED, FILL);
    image.flipVertically();
    image.writeTGAFile("output.tga");
}