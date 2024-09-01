#include "tgabasic.h"

using namespace tgabasic;

int main() {
    TGAImage image(1920,1080, 3);
    drawTriangle({960, 1080}, {1920, 0}, {0,0}, image,  ColorPalette::RED, FILL);
    image.writeTGAFile("output.tga");
}