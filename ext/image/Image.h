#ifndef EXT__IMAGE__IMAGE_H
#define EXT__IMAGE__IMAGE_H

#include "../macro.h"

class Image {
    PROTECTED_FILED_PUBLIC_GETTER(int, width, getWidth);
    PROTECTED_FILED_PUBLIC_GETTER(int, height, getHeight);
};

#endif