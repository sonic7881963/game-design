#include "sepia.h"

using namespace std;

SepiaImage::SepiaImage(Image* core) : Decorator(core) {}

void SepiaImage::render(PPM& ppm) {
    core->render(ppm);

    const int colourMax = 255;
    int width = ppm.getWidth();
    int height = ppm.getHeight();
    vector<Pixel>& pixels = ppm.getPixels();

   for (int i = 0; i < width * height; ++i) {
        Pixel& p = pixels[i];
        Pixel np;

        np.r = p.r * 0.393 + p.g * 0.769 + p.b * 0.189;
        np.g = p.r * 0.349 + p.g * 0.686 + p.b * 0.168;
        np.b = p.r * 0.272 + p.g * 0.534 + p.b * 0.131;

        np.r = np.r > colourMax ? colourMax : np.r;
        np.g = np.g > colourMax ? colourMax : np.g;
        np.b = np.b > colourMax ? colourMax : np.b;

        p = np;
    }
}
