#ifndef EXT__IMAGE__GRAY_IMAGE_H
#define EXT__IMAGE__GRAY_IMAGE_H

#include "../misc/macros.h"
#include "../math/Matrix.h"
#include "RGBAImage.h"

NS_EXT_BEGIN

template<typename T>
class GrayImage : public Matrix<T> {
    typedef Matrix<T> Base;
public:
    template<typename T1>
    GrayImage(const RGBAImage<T1>& image): Base(image.getWidth(), image.getHeight()) {
        //Base(image.getWidth(),image.getHeight());
        T* p = Base::data;
        RGBAColor<T1>* p1 = image.data;
        FOR(Base::width * Base::height) {
            *p = p1->ToGray();
            p++;
            p1++;
        }
    }
};

NS_EXT_END
#endif