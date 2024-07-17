#ifndef __FLIP_H__
#define __FLIP_H__

#include "decorator.h"

class FlipImage : public Decorator {
public:
    FlipImage(Image* core);
    void render(PPM& ppm) override;

};

#endif
