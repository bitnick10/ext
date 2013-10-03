#ifndef EXT__MATH__SET_H
#define EXT__MATH__SET_H

#include <iostream>
#include <list>

#include "../misc/macros.h"
#include "../image/Image.h"
#include "Matrix.h"

NS_EXT_BEGIN

template<typename T>
class Set:public std::list<T>{
};

NS_EXT_END
#endif