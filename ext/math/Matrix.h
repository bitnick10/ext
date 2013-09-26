#ifndef EXT__MATH__MATRIX_H
#define EXT__MATH__MATRIX_H

#include "../ext.h"
#include <iostream>
using namespace std;

template<typename T>
class Matrix {
public:
    PRIVATE_FILED_PUBLIC_GETTER(int , width, getWidth);
    PRIVATE_FILED_PUBLIC_GETTER(int , height, getHeight);
    T* data;
public:
    T* GetDataPointer() {
        return data;
    }
    bool IsSquare() const {
        return this->width == this->height;
    }
public:
    // constrcutor
    Matrix() {
        this->width = 0;
        this->height = 0;
        this->data = nullptr;
    }
    Matrix(int width, int height) {
        this->width = width;
        this->height = height;
        this->data = (T*) malloc(width * height * sizeof(T));
    }
    Matrix(T* data, int width, int height) error() {
        this->width = width;
        this->height = height;
        this->data = (T*)malloc(width * height * sizeof(T));
		if(this->data==nullptr){
			Error::getInstance()->SetLastError("Matrix malloc error");
			return ;
		}
        memcpy(this->data, data, sizeof(T)*this->width * this->height);
    }
    ~Matrix() {
        if(this->data != nullptr) {
            free(this->data);
            data = nullptr;
        }
    }
public:
    bool operator ==(Matrix& right) {
        if(this->height == right.height && this->width == right.width && 0 == memcmp(this->data, right.data, sizeof(T)*this->width * this->height)) {
            return true;
        } else {
            return false;
        }
    }

    bool operator !=(Matrix& right) {
        return !(*this == right);
    }

    friend ostream& operator<<(ostream& o, const Matrix& matrix) {
        T* data = matrix.data;
        FOR( matrix.width * matrix.height ) {
            o << *data++ << ",";
            o << ",";
        }
        return o;
    }
public:
    // algorithm
    template<typename T1, typename T2>
    static Matrix<T> Product(Matrix<T1>& a, Matrix<T2>& b) {
        if(a.getWidth() != b.getHeight()    ) {
            return Matrix<T>(nullptr, 0, 0);
        }
        Matrix<T> ret(a.getWidth(), a.getHeight());
        T1* p1 = a.data;
        T2* p2 = b.data;
        T* p = ret.data;
        for(int i = 0; i < ret.getWidth()*ret.getHeight(); i++) {
            *p++ = (*p1++) * (*p2++);
        }
        return ret;
    }
};
#endif