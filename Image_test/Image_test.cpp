#include <ext/ext.h>

#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>

USING_NS_EXT

void debug() {
}

void main() {
    debug();
    Describe("GrayImage<byte>", []() {
        It("should convert from RGBAImage<byte>", []() {
            RGBAImage<byte> rgbaImage("TestResources/rgbw_2x2.bmp");
            GrayImage<byte> grayImage = rgbaImage;
            Expect((int)grayImage.GetElement(0, 0)).ToBe(75);
            Expect((int)grayImage.GetElement(1, 0)).ToBe(149);
            Expect((int)grayImage.GetElement(0, 1)).ToBe(29);
            Expect((int)grayImage.GetElement(1, 1)).ToBe(255);
        });
    });
    Describe("RGBAImage<byte>", []() {
        It("should be able to read data from bmp file", []() {
            RGBAImage<byte> image("TestResources/rgbw_2x2.bmp");
            Expect(image.GetElement(0, 0)).ToBe(RGBAColor<byte>(255, 0, 0, 255));
            Expect(image.GetElement(1, 0)).ToBe(RGBAColor<byte>(0, 255, 0, 255));
            Expect(image.GetElement(0, 1)).ToBe(RGBAColor<byte>(0, 0, 255, 255));
            Expect(image.GetElement(1, 1)).ToBe(RGBAColor<byte>(255, 255, 255, 255));
        });
        Describe("when read lena.bmp finished", []() {
            RGBAImage<byte> image("TestResources/Lena.bmp");
            It("should be able to get width and height", [&image]() {
                Expect(image.getHeight()).ToBe(512);
                Expect(image.getWidth()).ToBe(512);
            });
            It("should be able to get pixel", [&image]() {
                Expect(image.GetElement(0, 0)).ToBe(RGBAColor<byte>(225, 138, 128, 255));
            });
            It("should be able to indexof sub image", [&image]() {
                RGBAImage<byte> sub1("TestResources/IndexOf/sub1.bmp");
                RGBAImage<byte> sub2("TestResources/IndexOf/sub2.bmp");
                RGBAImage<byte> sub3("TestResources/IndexOf/sub3.bmp");
                Expect(image.IndexOf(sub1)).ToBe(Coord<short>(0, 0));
                Expect(image.IndexOf(sub2)).ToBe(Coord<short>(1, 500));
                Expect(image.IndexOf(sub3)).ToBe(Coord<short>(122, 237));
            });
        });
    });

    Benchmark("read lene.bmp", []() {
        RGBAImage<byte> image("TestResources/Lena.bmp");
    });
    Benchmark("indexof lene.bmp", []() {
        RGBAImage<byte> sub3("TestResources/IndexOf/sub3.bmp");
        RGBAImage<byte> image("TestResources/Lena.bmp");
        image.IndexOf(sub3);
    });
}