#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include "image.h"

class Decorator : public Image {
protected:
    Image* core;

public:
    Decorator(Image* core);
    ~Decorator();

};







#endif
