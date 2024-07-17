#include "rotate.h"
#include <utility>


RotateImage::RotateImage(Image* core) : Decorator{core} {}

void RotateImage::render(PPM& ppm) {
    core->render(ppm);

    int width = ppm.getWidth();
    int height = ppm.getHeight();
    std::vector<Pixel>& pixels = ppm.getPixels();
    std::vector<Pixel> newPixels(width * height);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            newPixels[i * height + j] 
            = pixels[width * (height - j - 1) + i];
        }
    }

    ppm.getPixels() = newPixels;
    std::swap(ppm.getWidth(), ppm.getHeight());
}
