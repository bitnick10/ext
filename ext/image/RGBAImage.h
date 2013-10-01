#ifndef EXT__IMAGE__RGBA_IMAGE_H
#define EXT__IMAGE__RGBA_IMAGE_H

#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

#include "../misc/macros.h"
#include "../math/Matrix.h"

NS_EXT_BEGIN

template<typename T>
class RGBAImage : public Matrix<RGBAColor<T>> {
    typedef Matrix<RGBAColor<T>> Base;
    typedef RGBAColor<T> Color;
public:
    //constructor
    RGBAImage(): Base() {}
    RGBAImage(RGBAImage& image): Base(image) { }
    RGBAImage(int width, int height): Base(width, height) { }
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
        BITMAPFILEHEADER file_header;
        BITMAPINFO bitmap_info;
        fstream file;
        file.open(filename, ios::in | ios::binary );
        assert(file);
        file.read((char*)&file_header, sizeof(BITMAPFILEHEADER));
        file.read((char*)&bitmap_info.bmiHeader, sizeof(BITMAPINFOHEADER));

        Base::width = bitmap_info.bmiHeader.biWidth;
        Base::height = bitmap_info.bmiHeader.biHeight;
        int spectrum = bitmap_info.bmiHeader.biBitCount / 8;
        int offset = 4 - spectrum * Base::width & 0x3;

        int  dataSize = Base::width * Base::height  * sizeof(Color) ;
        Base::data = (Color*)malloc(dataSize);
        assert(Base::data);

        //read file into memory
        char* imageData =  (char*)malloc(bitmap_info.bmiHeader.biSizeImage);
        file.seekg(file_header.bfOffBits);
        file.read((char*)imageData, dataSize);
        char* pImage = imageData;

        // only support byte now
        assert(typeid(Color) == typeid(RGBAColor<byte>));

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
                pImage += offset;
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
                pImage += offset;
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
    void SaveAs(char* filename) {
        int spectrum = 3;
        int offset = 4 - spectrum * Base::width & 0x3;
        int data_size = width * height * spectrum + offset * height;

        BITMAPFILEHEADER file_header;
        file_header.bfType				= MAKEWORD('B', 'M');
        file_header.bfSize				= 54 +  data_size;
        file_header.bfReserved1		= 0;
        file_header.bfReserved2		= 0;
        file_header.bfOffBits			= 54;
        BITMAPINFO bitmap_info;
        BITMAPINFOHEADER* info_header = &bitmap_info.bmiHeader;
        info_header->biSize						= 40;
        info_header->biWidth					= width;
        info_header->biHeight					= height;
        info_header->biPlanes					= 0;
        info_header->biBitCount				= spectrum * 8; //bitmap.bmBitsPixel;
        info_header->biCompression			= 0;
        info_header->biSizeImage				= data_size; // bitmap.bmWidthBytes * bitmap.bmHeight;
        info_header->biXPelsPerMeter		= 0;
        info_header->biYPelsPerMeter		= 0;
        info_header->biClrUsed					= 0;
        info_header->biClrImportant			= 0;

        byte* image_data =  (byte*)malloc(data_size);
        assert(image_data);
        byte* writer = image_data;

        fstream file(filename, ios::out | ios::binary);
        file.write((char*)&file_header, sizeof(BITMAPFILEHEADER));
        file.write((char*)&bitmap_info, bitmap_info.bmiHeader.biSize);
        for(int y = 0; y < Base::height ; y++) {
            byte* p = (byte*)Base::GetDataPointer(0, Base::height - 1 - y);
            for(int x = 0; x < Base::width; x++) {
                writer[2] = p[0] ;
                writer[1] = p[1] ;
                writer[0] = p[2] ;
                p += 4;
                writer += spectrum;
            }
            writer += offset;
        }
        file.write((char*)image_data, height * width * spectrum);
        file.close();
    }
};

NS_EXT_END
#endif