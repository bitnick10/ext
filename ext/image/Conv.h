#ifndef EXT__IMAGE__CONV_H
#define EXT__IMAGE__CONV_H

#include "../math/Matrix.h"
#include "../misc/macros.h"
#include "GrayImage.h"
#include "RGBAImage.h"

NS_EXT_BEGIN

#define GRAY_IMAGE(image) Conv::ToGrayImage(image);
#define GRBA_IMAGE(image) Conv::ToRGBAImage(image);

class Conv {
public:
    template<typename T>
    static GrayImage<T> ToGrayImage(RGBAImage<T>& image) {
        GrayImage<T> ret(image.getWidth(), image.getHeight());
        T* p = ret.data;
        RGBAColor<T>* p1 = image.data;
        FOR(ret.getWidth() * ret.getHeight()) {
            *p = p1->ToGray();
            p++;
            p1++;
        }
        return ret;
    }
    template<typename T>
    static RGBAImage<T> ToRGBAImage(GrayImage<T>& image) {
        RGBAImage<T> ret(image.getWidth(), image.getHeight());
        RGBAColor<T>* p = ret.data;
        T* p1 = image.data;
        FOR(ret.getWidth() * ret.getHeight()) {
            p->R = *p1;
            p->G = *p1;
            p->B = *p1;
            p->A = (T)~(T)0;
            p++;
            p1++;
        }
        return ret;
    }
};

NS_EXT_END
#endif