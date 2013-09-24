#ifndef EXT__MATH__MATRIX_H
#define EXT__MATH__MATRIX_H

#include "../macro.h"

class Matrix {
    PRIVATE_FILED_PUBLIC_GETTER(int , width, getWidth);
    PRIVATE_FILED_PUBLIC_GETTER(int , height, getHeight);
public:
	bool IsSquare() const {
		return this->width==this->height;
	}
};

#endif