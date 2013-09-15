#ifndef EXT__IMAGE__COORD_H
#define EXT__IMAGE__COORD_H

#include <iostream>
using namespace std;

template<typename T>
struct Coord {
    T X, Y;
    Coord() {}
    Coord(T X, T Y) {
        this->X = X;
        this->Y = Y;
    }
    friend ostream& operator<<(ostream& o , const Coord& color) {
        if(	typeid(color.X) == typeid(byte)) {
            o << (short)color.X << "," << (short)color.Y ;
        } else {
            o << color.X << "," << color.Y ;
        }
        return o;
    }
    bool operator ==(const Coord& right) const {
        if( this->X == right.X && this->Y == right.Y ) {
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(const Coord& right) {
        return !(*this == right);
    }
};
#endif