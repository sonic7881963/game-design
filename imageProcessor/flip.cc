#include "flip.h"
#include <utility>


FlipImage::FlipImage(Image* core) : Decorator{core} {}

void FlipImage::render(PPM& ppm) {
  core->render(ppm);

  int height = ppm.getHeight();
  int width = ppm.getWidth();
  std::vector<Pixel>& pixels = ppm.getPixels();

  for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width / 2; ++col) {
            std::swap(pixels[row * width + col], 
            pixels[row * width + (width - col - 1)]);
        }
  }

}

