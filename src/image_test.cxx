//I have to test set_pixels

import Image;

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

#include "third_party/lodepng.h"

class Rand_int {
	public:
	Rand_int(int low, int high) : dist{low,high} { }
	int operator()() { return dist(re); }
	void seed(int s) { re.seed(s); }
	private:
		std::default_random_engine re;
		std::uniform_int_distribution<> dist;
};

class ImageTest : public testing::Test {
    protected:
        // I initialize random_uint8_t in the member initializer list bc I have to
        ImageTest() : random_uint8_t(0, 255), random_image_dimension(1, 255){
            random_uint8_t.seed(std::chrono::system_clock::now().time_since_epoch().count());
            random_uint8_t = Rand_int(0, 255);
            random_image_dimension = Rand_int(1, 255);
            width = random_image_dimension();
            height = random_image_dimension();
            for (int i = 0; i < width * height * 3; i++) {
                random_pixels.push_back(random_uint8_t());
            }
            test_image = Image(width, height, 255);
        }
        
        ~ImageTest() {
            random_pixels.clear();
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // Class members declared here can be used by all tests in the test suite
        // for Foo.
        Rand_int random_uint8_t;
        Rand_int random_image_dimension;
        unsigned width, height;
        std::vector<uint8_t> random_pixels;
        Image test_image;
        Pixel empty_pixel;
};

TEST_F(ImageTest, set_pixels_doesnt_explode) {
    test_image.set_pixels(random_pixels);
    for (int j = 0; j < 10; j++)
    {
        int i = 0;
        for (const Pixel& pixel : test_image.pixels)
        {
            EXPECT_EQ(pixel.r, random_pixels[i]) << i << "th Pixel's r: " << pixel.r << " Expected Value: " << random_pixels[i] << std::endl;
            EXPECT_EQ(pixel.g, random_pixels[i+1]) << i << "th Pixel's g: " << pixel.g << " Expected Value: " << random_pixels[i+1] << std::endl;
            EXPECT_EQ(pixel.b, random_pixels[i+2]) << i << "th Pixel's b: " << pixel.b << " Expected Value: " << random_pixels[i+2] << std::endl;
            i+=3;
        }
    }
}

TEST_F(ImageTest, pixel_cin_works) {
    std::istringstream input("255 0 0");
    input >> empty_pixel;
    EXPECT_EQ(empty_pixel.r, 255);
    EXPECT_EQ(empty_pixel.g, 0);
    EXPECT_EQ(empty_pixel.b, 0);
}

TEST_F(ImageTest, image_pixels_constructor_works) {
    test_image.set_pixels(random_pixels);
    int i = 0;
    for (const Pixel& pixel : test_image.pixels)
    {
        EXPECT_EQ(pixel.r, random_pixels[i]) << i << "th Pixel's r: " << pixel.r << " Expected Value: " << random_pixels[i] << std::endl;
        EXPECT_EQ(pixel.g, random_pixels[i+1]) << i << "th Pixel's g: " << pixel.g << " Expected Value: " << random_pixels[i+1] << std::endl;
        EXPECT_EQ(pixel.b, random_pixels[i+2]) << i << "th Pixel's b: " << pixel.b << " Expected Value: " << random_pixels[i+2] << std::endl;
        i+=3;
    }
}

TEST_F(ImageTest, read_png_works){
    std::vector<unsigned char> random_image;
    lodepng::encode(random_image, random_pixels, width, height, LCT_RGB);
    lodepng::save_file(random_image, "random_image.png");
    test_image.read_png("random_image.png");
    int i = 0;
    for (const Pixel& pixel : test_image.pixels)
    {
        EXPECT_EQ(pixel.r, random_pixels[i]) << i << "th Pixel's r: " << pixel.r << " Expected Value: " << random_pixels[i] << std::endl;
        EXPECT_EQ(pixel.g, random_pixels[i+1]) << i << "th Pixel's g: " << pixel.g << " Expected Value: " << random_pixels[i+1] << std::endl;
        EXPECT_EQ(pixel.b, random_pixels[i+2]) << i << "th Pixel's b: " << pixel.b << " Expected Value: " << random_pixels[i+2] << std::endl;
        i+=3;
    }
}
