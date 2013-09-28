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
    T Get() {
        return data[0];
    }
    T Get(int x, int y) {
        return data[y * width + x];
    }
    T* GetDataPointer() {
        return data;
    }
    bool IsSquare() const {
        return this->width == this->height;
    }
public:
    // constrcutor
    error() Matrix() {
        this->width = 0;
        this->height = 0;
        this->data = nullptr;
    }
    error() Matrix(Matrix& matrix) {
        this->width = matrix.width;
        this->height = matrix.height;
        int size = this->width * this->height * sizeof(T);
        this->data = (T*)malloc(size);
        if(this->data == nullptr) {
            Error::getInstance()->SetLastError("Matrix malloc error");
            return ;
        }
        memcpy(this->data, matrix.data, size);
    }
    error() Matrix(int width, int height)  {
        this->width = width;
        this->height = height;
        int size = this->width * this->height * sizeof(T);
        this->data = (T*)malloc(size);
        if(this->data == nullptr) {
            Error::getInstance()->SetLastError("Matrix malloc error");
            return ;
        }
    }
    error() Matrix(T* data, int width, int height)  {
        this->width = width;
        this->height = height;
        int size = this->width * this->height * sizeof(T);
        this->data = (T*)malloc(size);
        if(this->data == nullptr) {
            Error::getInstance()->SetLastError("Matrix malloc error");
            return ;
        }
        memcpy(this->data, data, size);
    }
    ~Matrix() {
        if(this->data != nullptr) {
            free(this->data);
            data = nullptr;
        }
    }
public:
    bool operator ==(Matrix& right)  {
        if(this->height == right.height && this->width == right.width && 0 == memcmp(this->data, right.data, sizeof(T)*this->width * this->height)) {
            return true;
        } else {
            return false;
        }
    }
    bool operator !=(Matrix& right) {
        return !(*this == right);
    }
    Matrix operator =(const Matrix& right) {
        this->~Matrix();
        this->width = right.width;
        this->height = right.height;
        int size = this->width * this->height * sizeof(T);
        this->data = (T*)malloc(size);
        if(this->data == nullptr) {
            Error::getInstance()->SetLastError("Matrix malloc error");
            return *this;
        }
        memcpy(this->data, right.data, size);
        return *this;
    }
    friend ostream& operator<<(ostream& o, const Matrix& matrix) {
        T* data = matrix.data;
        FOR( matrix.width * matrix.height - 1 ) {
            o << *data++ << ",";
        }
        o << *data++;
        return o;
    }
public:
    // algorithm

public:
    // static algorithm
    template<typename T1, typename T2>
    static Matrix<T> DotProduct(const Matrix<T1>& a, const Matrix<T2>& b) {
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
    template<typename T1, typename T2>
    static Matrix<T> Product(const Matrix<T1>& a, const  Matrix<T2>& b) {
        if(a.getWidth() != b.getHeight()    ) {
            return Matrix<T>(nullptr, 0, 0);
        }
        Matrix<T> ret(b.getWidth(), a.getHeight());
        T1* p1 = a.data;
        T2* p2 = b.data;
        T* p = ret.data;
        for(int row = 0; row < a.getHeight(); row++) {
            T2* p2Calc = p2;
            for(int col = 0; col < b.getWidth(); col++, p++) {
                T1* p1Calc = p1;
                p2Calc = p2 + col;
                *p = 0;
                FOR(a.getWidth()) {
                    int value1 = *p1Calc;
                    int value2 = *p2Calc;
                    *p += value1 * value2;
                    p1Calc++;
                    p2Calc += b.getWidth();
                }
            }
            p1 += a.getWidth();
        }
        return ret;
    }
    static Matrix<T> Minor(Matrix<T>&matrix, int dx, int dy) {
        Matrix<T> ret(matrix.getWidth() - 1, matrix.getHeight() - 1);
        T* p = ret.data;
        T* pm = matrix.data;
        for(int y = 0; y < matrix.getHeight(); y++) {
            for(int x = 0; x < matrix.getWidth() ; x++) {
                if(x == dx || y == dy) {
                    *pm++;
                    continue;
                }
                *p++ = *pm++;
            }
        }
        return ret;
    }
    static T Det(Matrix<T>&matrix) {
        if( matrix.getHeight() <= 2) {
            if(matrix.getHeight() == 2) {
                return matrix.data[0] * matrix.data[3] - matrix.data[1] * matrix.data[2];
            } else if(matrix.getHeight() == 1) {
                return matrix.data[0];
            }
        }
        T* p = matrix.data;
        T ret = *p * Cofactor(matrix, 0, 0);
        for(int x = 1; x < matrix.getWidth(); x++) {
            ret += *++p * Cofactor(matrix, x, 0);
        }
        return ret;
    }
    static T Cofactor(Matrix<T>& matrix, int x, int y) {
        Matrix<T> minor = Minor(matrix, x, y);
        if(x + y % 2 == 1) {
            return -1 * Det(minor);
        } else {
            return Det(minor);
        }
    }
    //template<typename T1, typename T2>
    //static Matrix<T> Conv(const Matrix<T1>& left, const  Matrix<T2>& right) ->decltype(left.dat[0]*right.data[0]) {
    //	if(a.getWidth() != b.getHeight()    ) {
    //		return Matrix<T>(nullptr, 0, 0);
    //	}
    //	Matrix<T> ret(a.getWidth(), a.getHeight());
    //	T1* p1 = a.data;
    //	T2* p2 = b.data;
    //	p1++;
    //	p2++;
    //	decltype(left.data[0]*right.data[0]) ret = left.data[0] * right.data[0];
    //	for(int i = 1; i < ret.getWidth()*ret.getHeight(); i++) {
    //		*p++ = (*p1++) * (*p2++);
    //	}
    //	return ret;
    //}
};
#endif