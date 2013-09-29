#ifndef EXT__IMAGE__RGBA_IMAGE_H11
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
class RGBAImage : public Matrix<RGBAColor<T>> {
    typedef Matrix<RGBAColor<T>> Base;
    typedef RGBAColor<T> CT;
public:
	//constructor
	RGBAImage(RGBAImage& image) {
        this->width = image.width;
        this->height = image.height;
        int size = width * height * sizeof(CT);
        this->data = (T*)malloc(size);
        assert(this->data);
        memcpy(this->data, image.data, size);
    }
	    RGBAImage(int width, int height) {
        this->width = width;
        this->height = height;
  int size = width * height * sizeof(CT);
        this->data = (T*)malloc(size);
        assert(this->data);
    }
    RGBAImage(char* filename) {
        ReadFromFile(filename);
    }
    void ReadFromFile(char* filename) {
        int len   = lstrlen(filename);
        TCHAR ch  = filename[len - 1];
        if(ch == 'g') {
            assert(false);
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

        Base::width = bmpInfo.bmiHeader.biWidth;
        Base::height = bmpInfo.bmiHeader.biHeight;
        int spectrum = bmpInfo.bmiHeader.biBitCount / 8;
        int readOffset = 4 - spectrum * Matrix::width & 0x3;

        int  dataSize = Base::width * Base::height  * sizeof(CT) ;
        Matrix::data = (CT*)malloc(dataSize);
        assert(Matrix::data);

        //read file into memory
        char* imageData =  (char*)malloc(bmpInfo.bmiHeader.biSizeImage);
        file.seekg(bmpFileHeader.bfOffBits);
        file.read((char*)imageData, dataSize);
        char* pImage = imageData;

        // only support byte now
        assert(typeid(CT) == typeid(RGBAColor<byte>));

        if(spectrum == 3)
            for(int y = 0; y < Base::height ; y++) {
                byte* p = (byte*)Base::GetDataPointer(0, Base::height - 1 - y);
                for(int x = 0; x < Base::width; x++) {
                    p[0] = pImage[2];
                    p[1] = pImage[1];
                    p[2] = pImage[0];
                    p[3] = 255;
                    //p[3] = (CT)~(CT)0; //T MAX, byte 255, uint16 65535
                    p += 4;
                    pImage += spectrum;
                }
                pImage += readOffset;
            }
        else if(spectrum == 4) {
            for(int y = 0; y < Base::height ; y++) {
                byte* p = (byte*)Base::GetDataPointer(0, Base::height - 1 - y);
                for(int x = 0; x < Base::width; x++) {
                    p[0] = pImage[3];
                    p[1] = pImage[2];
                    p[2] = pImage[1];
                    p[3] = 255;
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
        file.close();
        return ;
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
            p = ( RGBAColor<T>*) Base::GetDataPointer(coord.X, coord.Y + subY);
            pSub = ( RGBAColor<T>*)subImage.GetDataPointer(0, subY);
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
};

NS_EXT_END
#endif