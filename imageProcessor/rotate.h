#ifndef __ROTATE_H__
#define __ROTATE_H__

#include "decorator.h"

class RotateImage : public Decorator {
public:
    RotateImage(Image* core);
    void render(PPM& ppm) override;

};

#endif
