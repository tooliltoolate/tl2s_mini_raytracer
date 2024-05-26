//I have to test set_pixels

import Image;

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

class ImageTest : public testing::Test {
    protected:
        ImageTest() {}


  // Class members declared here can be used by all tests in the test suite
  // for Foo.
    Image test_image {3, 2, 255};
    std::vector<uint8_t> wikipedia {255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0, 255, 255, 255, 0, 0, 0};
    std::vector<uint8_t> all_white_3 {0,0,0,0,0,0,0,0,0};
    std::vector<uint8_t> all_black_3 {255,255,255,255,255,255,255,255,255};
    std::vector<uint8_t> all_random_3 {'a','a','a','a','a','a','a','a','a'};
    std::vector<uint8_t> all_white_4 {0,0,0,0,0,0,0,0,0,0,0,0};
    std::vector<uint8_t> all_black_4 {255,255,255,255,255,255,255,255,255,255,255,255};
};

TEST_F(ImageTest, set_pixels_doesnt_explode) {
    test_image.set_pixels(wikipedia);
    int i = 0;
    for (const Pixel& pixel : test_image.pixels)
    {
        EXPECT_EQ(pixel.r, wikipedia[i]) << i << "th Pixel's r: " << pixel.r << " Expected Value: " << wikipedia[i] << std::endl;
        EXPECT_EQ(pixel.g, wikipedia[i+1]) << i << "th Pixel's g: " << pixel.g << " Expected Value: " << wikipedia[i+1] << std::endl;
        EXPECT_EQ(pixel.b, wikipedia[i+2]) << i << "th Pixel's b: " << pixel.b << " Expected Value: " << wikipedia[i+2] << std::endl;
        i+=3;
    }
    test_image.set_pixels(all_random_3);
    i = 0;
    for (const Pixel& pixel : test_image.pixels)
    {
        EXPECT_EQ(pixel.r, all_random_3[i]) << i << "th Pixel's r: " << pixel.r << " Expected Value: " << all_random_3[i] << std::endl;
        EXPECT_EQ(pixel.g, all_random_3[i+1]) << i << "th Pixel's g: " << pixel.g << " Expected Value: " << all_random_3[i+1] << std::endl;
        EXPECT_EQ(pixel.b, all_random_3[i+2]) << i << "th Pixel's b: " << pixel.b << " Expected Value: " << all_random_3[i+2] << std::endl;
        i+=3;
    }
}
