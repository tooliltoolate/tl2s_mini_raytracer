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
        Rand_int() : dist{1,255} { }
	Rand_int(int low, int high) : dist{low,high} { }
	int operator()() { return dist(re); }
	void seed(int s) { re.seed(s); }
	private:
		std::default_random_engine re;
		std::uniform_int_distribution<> dist;
};

class ImageTest : public testing::Test {
    protected:
        Rand_int random_uint8_t;
        Rand_int random_image_dimension;
        unsigned width, height;
        std::vector<uint8_t> random_pixels;
        Image<uint8_t, (uint8_t)3> test_image;
        Pixel<uint8_t, (uint8_t)3> empty_pixel;

        ImageTest()
        {
            random_uint8_t = Rand_int(0, 255);
            random_image_dimension = Rand_int(1, 255);
            random_uint8_t.seed(std::chrono::system_clock::now().time_since_epoch().count());
            random_image_dimension.seed(std::chrono::system_clock::now().time_since_epoch().count());
            width = random_image_dimension();
            height = random_image_dimension();
            for (int i = 0; i < width * height * 3; i++) {
                random_pixels.push_back(random_uint8_t());
            }
            test_image = Image<uint8_t, (uint8_t)3>{.width = width, .height = height, .max_value = 255};
        }
        
        ~ImageTest() {
            random_pixels.clear();
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // Class members declared here can be used by all tests in the test suite
        // for Foo.
};

TEST_F(ImageTest, set_pixels_doesnt_explode) {
    for (int j = 0; j < 10; j++)
    {
        test_image.set_pixels(random_pixels);
        int i = 0;
        for (const Pixel<uint8_t, (uint8_t)3>& pixel : test_image.pixels)
        {
            EXPECT_EQ(pixel.values[i], random_pixels[i]) << i << "th Pixel's r: " << pixel.values[i] << " Expected Value: " << random_pixels[i] << std::endl;
            EXPECT_EQ(pixel.values[i + 1], random_pixels[i+1]) << i << "th Pixel's g: " << pixel.values[i + 1] << " Expected Value: " << random_pixels[i+1] << std::endl;
            EXPECT_EQ(pixel.values[i + 2], random_pixels[i+2]) << i << "th Pixel's b: " << pixel.values[i + 2] << " Expected Value: " << random_pixels[i+2] << std::endl;
            i+=3;
        }
        for (int c = 0; c < width * height * 3; c++) {
            random_pixels.push_back(random_uint8_t());
        }
    }
}

TEST_F(ImageTest, read_png_works){
    unsigned _width, _height;
    std::vector<unsigned char> random_image;
    lodepng::encode(random_image, random_pixels, _width, _height, LCT_RGB);
    lodepng::save_file(random_image, "random_image.png");
    test_image.read_png("random_image.png");
    int i = 0;
    for (const Pixel<uint8_t, (uint8_t)3>& pixel : test_image.pixels)
    {
        EXPECT_EQ(pixel.values[i], random_pixels[i]) << i << "th Pixel's r: " << pixel.values[i] << " Expected Value: " << random_pixels[i] << std::endl;
        EXPECT_EQ(pixel.values[i + 1], random_pixels[i+1]) << i << "th Pixel's g: " << pixel.values[i + 1] << " Expected Value: " << random_pixels[i+1] << std::endl;
        EXPECT_EQ(pixel.values[i + 2], random_pixels[i+2]) << i << "th Pixel's b: " << pixel.values[i + 2] << " Expected Value: " << random_pixels[i+2] << std::endl;
        i+=3;
    }
}
