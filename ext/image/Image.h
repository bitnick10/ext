#ifndef EXT__IMAGE__IMAGE_H
#define EXT__IMAGE__IMAGE_H

#include "../misc/macros.h"
#include "BlackImage.h"
#include "GrayImage.h"
#include "RGBAImage.h"

NS_EXT_BEGIN

#define Black BlackImage<byte>
#define Gray GrayImage<byte>
#define RGBA RGBAImage<byte>

template<typename T>
class Image: public T {
public:
    Image(): T {}
    Image(Image<Black>& image) {
        operator=(image);
    }
    Image(Image<Gray>& image) {
        operator=(image);
    }
    Image(Image<RGBA>& image) {
        operator=(image);
    }
    Image(char* filename): T(filename) {}
    Image(int width, int height): T(width, height) {}
public:
    Image& operator=(Image<Black>& image) {
        if(typeid(T) == typeid(Black)) {
            destruct();
            init(image.data, image.getWidth(), image.getHeight());
        } else if(typeid(T) == typeid(Gray)) { //Black to Gray
            assert(false);
            destruct();
            init(image.data, image.getWidth(), image.getHeight());
        } else {
            assert(false);
        }
        return *this;
    }
    Image& operator=(Image<Gray>& image) {
        if(typeid(T) == typeid(Gray)) {
            destruct();
            init(image.data, image.getWidth(), image.getHeight());
        } else if(typeid(T) == typeid(Black)) { // Gary to Black
            destruct();
            init(image.getWidth(), image.getHeight());
            byte* dst = (byte*)data;
            byte* src = image.data;
            FOR(width * height) {
                *src > (255 >> 1) ? *dst = WhiteColor : *dst = BlackColor;
                dst++;
                src++;
            }
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
        } else if(typeid(T) == typeid(Black)) { // RGBA to Black
            Image<Gray> grayImage = image;
            *this = grayImage;
        } else if(typeid(T) == typeid(Gray)) { // RGBA to Gray
            destruct();
            init(image.getWidth(), image.getHeight());
            byte* p = (byte*)data;
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