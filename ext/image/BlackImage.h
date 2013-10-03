#ifndef EXT__IMAGE__BLACK_IMAGE_H
#define EXT__IMAGE__BLACK_IMAGE_H

#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

#include "../misc/macros.h"
#include "../math/Matrix.h"

NS_EXT_BEGIN

#define BlackColor 1
#define WhiteColor 0

template<typename T>
class BlackImage : public Matrix<T> {
    typedef Matrix<T> Base;
public:
    BlackImage(): Base() {}
    BlackImage(int width, int height): Base(width, height) {}
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
                if(p[0] == BlackColor) {
                    writer[2] = 0 ;
                    writer[1] = 0 ;
                    writer[0] = 0 ;
                } else {
                    writer[2] = 255 ;
                    writer[1] = 255 ;
                    writer[0] = 255 ;
                }
                p += 1;
                writer += spectrum;
            }
            writer += offset;
        }
        file.write((char*)image_data, data_size);
        file.close();
    }
};

NS_EXT_END
#endif