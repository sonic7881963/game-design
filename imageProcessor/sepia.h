#ifndef __SEPIA_H__
#define __SEPIA_H__

#include "decorator.h"

class SepiaImage : public Decorator {
public:
    SepiaImage(Image* core);
    void render(PPM& ppm) override;

};

#endif
