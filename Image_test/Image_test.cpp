#include <ext/ext.h>

#include <iostream>
#include <vector>
#include <algorithm>

USING_NS_EXT

void debug() {
    Image<RGBA> image("C:\\plane.bmp");
	//image.SaveAs("C:\\circle2.bmp");
	Image<Black> blackImage=image;
	blackImage.SaveAs("C:\\plane1.bmp");
	blackImage = Erosion(blackImage);
	blackImage.SaveAs("C:\\plane2.bmp");
	//cout <<grayImage[0][0];
	//Image<Black>  blackImage = grayImage;
	//blackImage.SaveAs("C:\\blackwhite.bmp");
    //Image<RGBA> rgbaImage("C:\\plane.bmp");
    ////Image<RGBA> rgbaImage("img/Lena.bmp");
    ////rgbaImage.SaveAs("C:\\r.bmp");
    ////return;
    //GrayImage<byte> grayImage = GRAY_IMAGE(rgbaImage) ;
    ////grayImage.SaveAs("C:\\gray.bmp");
    //GrayImage<byte> x = Matrix<byte>::SobelFilterX(grayImage);
    //x.SaveAs("C:\\result_x.bmp");
    //GrayImage<byte> y = Matrix<byte>::SobelFilterY(grayImage);
    //y.SaveAs("C:\\result_y.bmp");
    //Image<RGBA> reader("C:\\r.bmp");
    //reader.SaveAs("C:\\r2.bmp");
}

void main() {
    debug();
    Describe("Image<Gray>", []() {
        It("should convert from Image<RGBA>", []() {
            Image<RGBA> rgbaImage("img/rgbw_2x2.bmp");
            Image<Gray> grayImage = rgbaImage ;
            Expect((int)grayImage.GetElement(0, 0)).ToBe(75);
            Expect((int)grayImage.GetElement(1, 0)).ToBe(149);
            Expect((int)grayImage.GetElement(0, 1)).ToBe(29);
            Expect((int)grayImage.GetElement(1, 1)).ToBe(255);
        });
    });
    Describe("Image<RGBA>", []() {
        It("should convert from GrayImage<byte>", []() {
            Image<RGBA> rgbaImage("img/rgbw_2x2.bmp");
            Image<Gray> grayImage = rgbaImage ;
            rgbaImage = grayImage ;
            Expect(rgbaImage.GetElement(0, 0)).ToBe(RGBAColor<byte>(75, 75, 75, 255));
            Expect(rgbaImage.GetElement(1, 0)).ToBe(RGBAColor<byte>(149, 149, 149, 255));
            Expect(rgbaImage.GetElement(0, 1)).ToBe(RGBAColor<byte>(29, 29, 29, 255));
            Expect(rgbaImage.GetElement(1, 1)).ToBe(RGBAColor<byte>(255, 255, 255, 255));
        });
        It("should be able to read data from bmp file", []() {
            Image<RGBA> image("img/rgbw_2x2.bmp");
            Expect(image.GetElement(0, 0)).ToBe(RGBAColor<byte>(255, 0, 0, 255));
            Expect(image.GetElement(1, 0)).ToBe(RGBAColor<byte>(0, 255, 0, 255));
            Expect(image.GetElement(0, 1)).ToBe(RGBAColor<byte>(0, 0, 255, 255));
            Expect(image.GetElement(1, 1)).ToBe(RGBAColor<byte>(255, 255, 255, 255));
        });
        Describe("when read lena.bmp finished", []() {
            Image<RGBA> image("img/Lena.bmp");
            It("should be able to get width and height", [&image]() {
                Expect(image.getHeight()).ToBe(512);
                Expect(image.getWidth()).ToBe(512);
            });
            It("should be able to get pixel", [&image]() {
                Expect(image.GetElement(0, 0)).ToBe(RGBAColor<byte>(225, 138, 128, 255));
            });
            It("should be able to indexof sub image", [&image]() {
                Image<RGBA> sub1("img/IndexOf/sub1.bmp");
                Image<RGBA> sub2("img/IndexOf/sub2.bmp");
                Image<RGBA> sub3("img/IndexOf/sub3.bmp");
                Expect(image.IndexOf(sub1)).ToBe(Coord<short>(0, 0));
                Expect(image.IndexOf(sub2)).ToBe(Coord<short>(1, 500));
                Expect(image.IndexOf(sub3)).ToBe(Coord<short>(122, 237));
            });
        });

    });

    Benchmark("read lene.bmp", []() {
        Image<RGBA> image("img/Lena.bmp");
    });
    Benchmark("indexof lene.bmp", []() {
        Image<RGBA> sub3("img/IndexOf/sub3.bmp");
        Image<RGBA> image("img/Lena.bmp");
        image.IndexOf(sub3);
    });
}