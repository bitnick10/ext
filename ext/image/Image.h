#ifndef EXT__IMAGE__IMAGE_H
#define EXT__IMAGE__IMAGE_H

#include "../misc/macros.h"
#include "GrayImage.h"
#include "RGBAImage.h"

NS_EXT_BEGIN

#define BW BWImage
#define Gray GrayImage<byte>
#define RGBA RGBAImage<byte>

template<typename T>
class Image: public T {
public:
    Image(): T {}
    Image(Image<RGBA>& image) {
        operator=(image);
    }
    Image(Image<Gray>& image) {
        operator=(image);
    }
    Image(char* filename): T(filename) {}
    Image(int width, int height): T(width, height) {}

    Image& operator=(Image<Gray>& image) {
        if(typeid(T) == typeid(Gray)) {
            destruct();
            init(image.data, image.getWidth(), image.getHeight());
        } else if(typeid(T) == typeid(RGBA)) { // Gary to RGBA
            destruct();
            init(image.getWidth(), image.getHeight());
            RGBAColor<byte>* p = (RGBAColor<byte>*)data;
            byte* src = image.data;
            FOR(width * height) {
                p->R = *src;
                p->G = *src;
                p->B = *src;
                p->A = (byte)~(byte)0;
                p++;
                src++;
            }
        } else {
            assert(false);
        }
        return *this;
    }
    Image& operator=(Image<RGBA>& image) {
        if(typeid(T) == typeid(RGBA)) {
            destruct();
            init(image.data, image.getWidth(), image.getHeight());
        } else if(typeid(T) == typeid(Gray)) { // RGBA to Gray
            destruct();
            init(image.getWidth(), image.getHeight());
            byte* p = data;
            RGBAColor<byte>* src = image.data;
            FOR(width * height) {
                *p = src->ToGray();
                p++;
                src++;
            }
        } else {
            assert(false);
        }
        return *this;
    }
};

NS_EXT_END
#endif