#ifndef EXT__MATH__MATRIX_H
#define EXT__MATH__MATRIX_H

#include <assert.h>
#include <iostream>
using namespace std;

#include "../image/Coord.h"
#include "../misc/log.h"

NS_EXT_BEGIN

template<typename T>
class Matrix {
    PROTECTED_FILED_PUBLIC_GETTER(int , width, getWidth);
    PROTECTED_FILED_PUBLIC_GETTER(int , height, getHeight);
public:
    T* data;
public:
    T GetElement() const {
        return data[0];
    }
    T GetElement(int x, int y) const {
        return data[y * width + x];
    }
    T* GetDataPointer(int x, int y) const {
        return data +  (y * this->width + x) ;
    }
    T* GetDataPointer() const {
        return data;
    }
    int Size() {
        return width * height * sizeof(T);
    }
    void SetElement(int x, int y, T& value) {
        T* p = GetDataPointer(x, y);
        *p = value;
    }
    bool IsSquare() const {
        return this->width == this->height;
    }
    T MaxElement() {
        T* p = data;
        T max = *p;
        FOR(width * height - 1) {
            if(max < *++p) {
                max = *p;
            }
        }
        return max;
    }
public:
    // constrcutor
    Matrix() : width(0), height(0), data(nullptr) {}
    Matrix(Matrix& matrix)  {
        init(matrix.data, matrix.width, matrix.height);
    }
    Matrix(int width, int height) {
        init(width, height);
    }
    Matrix(void* data, int width, int height)  {
        init(data, width, height);
    }
    ~Matrix() {
        destruct();
    }
protected:
    void init(int width, int height) {
        this->width = width;
        this->height = height;
        int size = Size();
        data = (T*)malloc(size);
        assert(data);
    }
    void init(void* data, int width, int height) {
        this->width = width;
        this->height = height;
        int size = Size();
        this->data = (T*)malloc(size);
        assert(this->data);
        memcpy(this->data, data, size);
    }
    void destruct() {
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
    Matrix& operator =(const Matrix& right) {
        this->~Matrix();
        this->width = right.width;
        this->height = right.height;
        int size = this->width * this->height * sizeof(T);
        this->data = (T*)malloc(size);
        assert(this->data != nullptr);
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
    Coord<short> IndexOf(Matrix<T>& sub) {
        Coord<short> coord (0, 0);
        for( ; coord.Y < getHeight() - sub.getHeight() + 1; coord.Y++) {
            for(coord.X = 0 ; coord.X < getWidth() - sub.getWidth() + 1; coord.X++) {
                if(ContainsAt(coord, sub)) {
                    return coord;
                }
            }
        }
        return Coord<short>(-1, -1);
    }
    bool ContainsAt(Coord<short> coord, Matrix<T>& sub) {
        INT32 subY;
        T* pSub;
        T* p;
        for(subY = 0; subY < sub.getHeight(); subY++) {
            p = GetDataPointer(coord.X, coord.Y + subY);
            pSub = sub.GetDataPointer(0, subY);
            for(int x = 0; x < sub.height; x++) {
                if(*p != *pSub) {
                    return false;
                }
                p++;
                pSub++;
            }
        }
        return true;
    }
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
        assert(a.getWidth() == b.getHeight());
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
        assert(matrix.IsSquare());
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
        assert(matrix.IsSquare());
        if( matrix.getHeight() <= 2) {
            if(matrix.getHeight() == 2) {
                return matrix.data[0] * matrix.data[3] - matrix.data[1] * matrix.data[2];
            } else if(matrix.getHeight() == 1) {
                return matrix.data[0];
            } else {
                assert(false);
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
        assert(matrix.IsSquare());
        Matrix<T> minor = Minor(matrix, x, y);
        if(x + y % 2 == 1) {
            return -1 * Det(minor);
        } else {
            return Det(minor);
        }
    }
    static Matrix<T> Sub(Matrix<T>& matrix, int ox, int oy, int width, int height) {
        assert(ox + width <= matrix.width);
        assert(oy + height <= matrix.height);
        Matrix<T> ret(width, height);
        T* p = ret.data;
        T* dp = matrix.GetDataPointer(ox, oy);
        for(int y = 0; y < height; y++) {
            T* cp = dp;
            for(int x = 0; x < width; x++) {
                *p++ = *cp++;
            }
            dp += matrix.width ;
        }
        return ret;
    }
    template<typename T1, typename T2>
    static auto ProductOne(const Matrix<T1>& m1, const  Matrix<T2>& m2) ->decltype(m1.data[0]*m2.data[0]) {
        assert(m1.getWidth() == m2.getWidth());
        assert(m1.getHeight() == m2.getHeight());
        T1* p1 = m1.data;
        T2* p2 = m2.data;
        decltype(m1.data[0]*m2.data[0]) ret = (*p1) * (*p2);
        FOR(m1.getWidth()*m1.getHeight() - 1) {
            ret += (*++p1) * (*++p2);
        }
        return ret;
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
NS_EXT_END
#endif