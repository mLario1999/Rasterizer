#include "tgabasic.h"
#include <vector>

using namespace tgabasic;

int main() {
    const int height = 1000;
    const int width = 1000;
    TGAImage image(height, width, 3);
    std::vector<int> z_buffer(height * width, std::numeric_limits<int>::min());
    drawTriangle({0, 0, 0}, {600, 300, 0}, {500, 500, 400}, image, ColorPalette::BLUE, FILL, z_buffer.data());
    drawTriangle({0, 0, -20}, {600, 300, 200}, {500, 500, 200}, image, ColorPalette::RED, FILL, z_buffer.data());
    drawTriangle({0, 0, -20}, {800, 500, 200}, {800, 800, 300}, image, ColorPalette::GREEN, FILL, z_buffer.data());
    image.flipVertically();
    image.writeTGAFile("output.tga");
}