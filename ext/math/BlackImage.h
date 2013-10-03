#ifndef EXT__MATH__GRAY_IMAGE_H
#define EXT__MATH__GRAY_IMAGE_H

#include "../misc/macros.h"
#include "../image/Image.h"
#include "Set.h"
#include "Matrix.h"

NS_EXT_BEGIN

Image<Black> Erosion(Image<Black>& image) {
    Image<Black> ret(image.getWidth(), image.getHeight());
	Set<Coord<short>> set;
	set.push_back(Coord<short>(0,0));
	set.push_back(Coord<short>(1,0));
    byte* dst = ret.data;
    byte* src = image.data;
    for(int y = 0; y < image.getHeight(); y++) {
        for(int x = 0; x < image.getWidth(); x++, dst++, src++) {
            if(*src == BlackColor) {
                for(auto iter = set.begin(); iter != set.end(); iter++) {
                    Coord<short> coord(x + (*iter).X, y + (*iter).Y);
                    if (image.GetElement(coord) != BlackColor) {
                        *dst = WhiteColor;
                        goto __next;
                    }
                }
                *dst = BlackColor;
            } else {
                *dst = WhiteColor;
            }
__next:;
        }
    }
    return ret;
}

NS_EXT_END
#endif