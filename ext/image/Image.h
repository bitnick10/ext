#ifndef EXT__IMAGE__IMAGE_H
#define EXT__IMAGE__IMAGE_H

#include "../misc/macros.h"
#include "BWImage.h"
#include "GrayImage.h"
#include "RGBAImage.h"

NS_EXT_BEGIN

#define RGBA RGBAImage<byte>
#define BW BWImage
#define Gray GrayImage<byte>

template<typename XXImage>
class Image: public XXImage {
public:
    Image(): XXImage {}
    Image(char* filename): XXImage(filename) {}
    Image(Image<RGBA>& image) {
        operator=(image);
    }

    Image& operator=(Image<RGBA>& image) {
        if(typeid(XXImage) == typeid(RGBA)) {
			assert(false);
            destruct();
            //init(image.GetDataPointer(),width,height);
        }  else if(typeid(XXImage) == typeid(Gray)) { // RGBA to Gray
            destruct();
            init(image.getWidth(), image.getHeight());
            byte* p = data;
            RGBAColor<byte>* p1 = image.data;
            FOR(width * height) {
                *p = p1->ToGray();
                p++;
                p1++;
            }
        } else {
            assert(false);
        }
        return *this;
    }
    Image& operator=(Image<Gray>& image) {
        if(typeid(XXImage) == typeid(Gray)) {
			assert(false);
            destruct();
        } else if(typeid(XXImage) == typeid(RGBA)) {// Gary to RGBA
            destruct();
			init(image.getWidth(),image.getHeight());
            RGBAColor<byte>* p = data;
            byte* p1 = image.data;
            FOR(width * height) {
                p->R = *p1;
                p->G = *p1;
                p->B = *p1;
                p->A = (byte)~(byte)0;
                p++;
                p1++;
            }
        } else {
            assert(false);
        }
        return *this;
    }
};

NS_EXT_END
#endif