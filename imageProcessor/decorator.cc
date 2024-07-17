#include "decorator.h"

Decorator::Decorator(Image* core) : core{core} {}

Decorator::~Decorator() {
    delete core;
}
