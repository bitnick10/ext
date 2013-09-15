#ifndef EXT__IMAGE__RGBA_COLOR_H
#define EXT__IMAGE__RGBA_COLOR_H

#include <iostream>
using namespace std;

template<typename T>
struct RGBAColor {
    T R, G, B, A;
	RGBAColor(){}
	RGBAColor(T R,T G,T B,T A){
		this->R=R;
		this->G=G;
		this->B=B;
		this->A=A;
	}
    friend ostream& operator<<(ostream& o , const RGBAColor& color) {
        if(	typeid(color.A) == typeid(byte)) {
            o << (short)color.R << "," << (short)color.G << "," << (short)color.B << "," << (short)color.A;
        } else {
            o << color.R << "," << color.G << "," << color.B << "," << color.A;
        }
        return o;
    }
    bool operator ==(const RGBAColor& right) const {
        if( this->R == right.R && this->G == right.G && this->B == right.B && this->A == right.A) {
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(const RGBAColor<T>& right) {
        return !(*this == right);
    }
};
#endif