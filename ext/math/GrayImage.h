#ifndef EXT__MATH__GRAY_IMAGE_H
#define EXT__MATH__GRAY_IMAGE_H

#include "../misc/macros.h"
#include "../image/Image.h"
#include "Matrix.h"

NS_EXT_BEGIN

template<typename image_t, typename data_t>
image_t SobelFilterX(Image<GrayImage<data_t>>& image) {
    char mat[] = {
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    };
    Matrix<char> filter(mat, 3, 3);
    image_t ret(image.getWidth(), image.getHeight());
    for(int y = 0; y < ret.getHeight() - 2; y++) {
        for(int x = 0; x < ret.getWidth() - 2; x++) {
            Matrix<data_t> sub = Matrix<data_t>::Sub(image, x, y, 3, 3);
            int int_value = Matrix<data_t>::ProductOne(sub, filter) >> 3;
            int abs_value = abs(int_value);
            data_t value = (byte)(abs_value);
            ret.SetElement(x, y, value);
        }
    }
    return ret;
}
template<typename T>
Image<GrayImage<T>> SobelFilterX(Image<GrayImage<T>>& image) {
    return SobelFilterX<Image<GrayImage<T>>>(image);
}
template<typename T>
Image<GrayImage<T>> SobelFilterY(Image<GrayImage<T>>& image) {
    char mat[] = {
        -1, -2, -1,
        0, 0, 0,
        1, 2, 1
    };
    Matrix<char> filter(mat, 3, 3);
    Image<GrayImage<T>> ret(image.getWidth(), image.getHeight());
    for(int y = 0; y < ret.getHeight() - 2; y++) {
        for(int x = 0; x < ret.getWidth() - 2; x++) {
            Matrix<T> sub = Matrix<T>::Sub(image, x, y, 3, 3);
            int int_value = Matrix<T>::ProductOne(sub, filter) >> 3;
            int abs_value = abs(int_value);
            T value = (byte)(abs_value);
            ret.SetElement(x, y, value);
        }
    }
    return ret;
}

Image<Gray> BlackWhite(Image<Gray>& image) {
    Image<Gray> ret(image.getWidth(), image.getHeight());
    byte* dst = (byte*)ret.data;
    byte* src = image.data;
    FOR(ret.getWidth()* ret.getHeight()) {
        *src > (255 >> 1) ? *dst = 255 : *dst = 0;
        dst++;
        src++;
    }
	return ret;
}

NS_EXT_END
#endif