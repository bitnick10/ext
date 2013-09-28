#ifndef EXT__IMAGE__RGBA_IMAGE_H
#define EXT__IMAGE__RGBA_IMAGE_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include "RGBAColor.h"
#include "Coord.h"
#include "Image.h"
#include "../math/Matrix.h"
#include "../ext.h"
using namespace std;

NS_EXT_BEGIN

template<typename T>
class RGBAImage : public Image {
    typedef T value_type ;
    T *data; //origin upper left
public:
    RGBAColor<T> GetPixel(int x, int y) {
        T *p = data + 4 * (y * Image::width + x);
        return *((RGBAColor<T>*)p);
    }
    void SetPixel(int x, int y, RGBAColor<T>& color) {
        RGBAImage<T> pColor = (RGBAImage<T>*) dataPtr(x, y);
        *pColor = color;
    }
    T* dataPtr(int x, int y) const {
        return data + 4 * (y * Image::width + x);
    }
public:
    //constructor
    RGBAImage(int width, int height) {
        this->width = width;
        this->height = height;
        int size = width * height * sizeof(T);
        this->data = (T*)malloc(size);
    }
    RGBAImage(char* filename) {
        ReadFromFile(filename);
    }
    void ReadFromFile(char* filename) {
        int len   = lstrlen(filename);
        TCHAR ch  = filename[len - 1];
        if(ch == 'g') {
            throw ;
            //ReadFromPngFile(filename);
        } else
            ReadFromBmpFile(filename);
    }
    void ReadFromBmpFile(char* filename) {
        BITMAPFILEHEADER bmpFileHeader;
        BITMAPINFO bmpInfo;
        fstream file;
        file.open(filename, ios::in | ios::binary);
        if(!file)
            return ;
        file.read((char*)&bmpFileHeader, sizeof(BITMAPFILEHEADER));
        file.read((char*)&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER));

        this->width = bmpInfo.bmiHeader.biWidth;
        this->height = bmpInfo.bmiHeader.biHeight;
        int spectrum = bmpInfo.bmiHeader.biBitCount / 8;
        int readOffset = 4 - spectrum * this->width & 0x3;

        int  dataSize = this->width * this->height * 4 * sizeof(T) ;
        this->data = (T*)malloc(dataSize);

        //read file into memory
        char* imageData =  (char*)malloc(bmpInfo.bmiHeader.biSizeImage);
        file.seekg(bmpFileHeader.bfOffBits);
        file.read((char*)imageData, dataSize);
        char* pImage = imageData;

        if(spectrum == 3)
            for(int y = 0; y < this->height ; y++) {
                T* p = dataPtr(0, this->height - 1 - y);
                for(int x = 0; x < this->width; x++) {
                    p[0] = pImage[2];
                    p[1] = pImage[1];
                    p[2] = pImage[0];
                    p[3] = (T)~(T)0; //T MAX, byte 255, uint16 65535
                    p += 4;
                    pImage += spectrum;
                }
                pImage += readOffset;
            }
        else if(spectrum == 4) {
            for(int y = 0; y < this->height ; y++) {
                T* p = dataPtr(0, this->height - 1 - y);
                for(int x = 0; x < this->width; x++) {
                    p[0] = pImage[3];
                    p[1] = pImage[2];
                    p[2] = pImage[1];
                    p[3] = (T)~(T)0;
                    p += 4;
                    pImage += spectrum;
                }
                pImage += readOffset;
            }
        }

        if (imageData != nullptr) {
            free(imageData);
            imageData = nullptr;
        }
        return ;

        if( spectrum == 3) {
            file.seekg(bmpFileHeader.bfOffBits);
            char* p = (char*)this->data;
            char temp[3];
            for(int y = this->height - 1; y >= 0 ; y--) {
                for(int x = 0; x < this->width; x++) {
                    file.read(temp, 3);
                    p[3] = (T)~(T)0; //T MAX, byte 255, uint16 65535
                    p += 4;
                }
                file.seekg(readOffset, ios::cur);
            }
        } else if( spectrum == 4 ) {
            file.seekg(bmpFileHeader.bfOffBits);
            file.read((char*)data, dataSize);
        } else {
            printf("error");
            //ASSERT(FALSE);
        }
        file.close();
    }
public:
    //destructor
    ~RGBAImage() {
        if (data != nullptr) {
            free(data);
            data = nullptr;
        }
    }
public:
    Coord<short> IndexOf(RGBAImage& subImage) {
        Coord<short> coord (0, 0);
        for( ; coord.Y < getHeight() - subImage.getHeight() + 1; coord.Y++) {
            for(coord.X = 0 ; coord.X < getWidth() - subImage.getWidth() + 1; coord.X++) {
                if(ContainsAt(coord, subImage)) {
                    return coord;
                }
            }
        }
        return Coord<short>(-1, -1);
    }
    bool ContainsAt(Coord<short> coord, RGBAImage& subImage) {
        INT32 subY;
        RGBAColor<T>* pSub;
        RGBAColor<T>* p;

        for(subY = 0; subY < subImage.getHeight(); subY++) {
            p = ( RGBAColor<T>*) dataPtr(coord.X, coord.Y + subY);
            pSub = ( RGBAColor<T>*)subImage.dataPtr(0, subY);
            for(int x = 0; x < subImage.height; x++) {
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
    void SaveAs(char* filenmae) {
        BITMAPFILEHEADER bitmapFileHeader;
        BITMAPFILEHEADER* pBitmapFileHeader = &bitmapFileHeader;
        pBitmapFileHeader->bfType				= MAKEWORD('B', 'M');
        pBitmapFileHeader->bfSize				= 54 +  this->height * this->width * this->spectrum;
        pBitmapFileHeader->bfReserved1		= 0;
        pBitmapFileHeader->bfReserved2		= 0;
        pBitmapFileHeader->bfOffBits			= 54;
        BITMAPINFO bitmapInfo;
        BITMAPINFO* pBitmapInfo = &bitmapInfo;
        int spectrum = 4;
        pBitmapInfo->bmiHeader.biSize						= 40;
        pBitmapInfo->bmiHeader.biWidth					= this->width;
        pBitmapInfo->bmiHeader.biHeight					= this->height;
        pBitmapInfo->bmiHeader.biPlanes					= 0;//bitmap.bmPlanes;
        pBitmapInfo->bmiHeader.biBitCount				= spectrum * 8; //bitmap.bmBitsPixel;
        pBitmapInfo->bmiHeader.biCompression			= 0;
        pBitmapInfo->bmiHeader.biSizeImage				= this->height * this->width * spectrum; // bitmap.bmWidthBytes * bitmap.bmHeight;
        pBitmapInfo->bmiHeader.biXPelsPerMeter		= 0;
        pBitmapInfo->bmiHeader.biYPelsPerMeter		= 0;
        pBitmapInfo->bmiHeader.biClrUsed					= 0;
        pBitmapInfo->bmiHeader.biClrImportant			= 0;

        fstream file(filename, ios::out | ios::binary);
        file.write((char*)pBitmapFileHeader, sizeof(BITMAPFILEHEADER));
        file.write((char*)pBitmapInfo, pBitmapInfo->bmiHeader.biSize);
        file.write((char*)data, this->height * this->width * this->spectrum);
        file.close();
    }
    RGBAImage MatrixFilter(Matrix<double> filter) {
        RGBAImage image(this->width, this->height);
        T* p = this->data;
        for(int y = 1; y < this->height - 1; y++) {
            for(int x = 1; x < this->width - 1; x++) {

            }
        }
    }
};

NS_EXT_END
#endif