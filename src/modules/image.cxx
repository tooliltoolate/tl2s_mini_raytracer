module;

#include <vector>
#include <iostream>

export module Image;

export int add(int a, int b) {
    return a + b;
}

export class Image
{
    const int channels, width, height, max_value;
    std::vector<int> pixels;
public:

    Image(int channels, int width, int height, int max_value) : channels(channels), width(width), height(height), max_value(max_value), pixels(width * height) {}

    void print_as_ppm() const
    {
        std::cout << "P" << channels << "\n" << width << " " << height << "\n" << max_value << "\n";
        for (int i = 0; i < width * height; i++)
        {
            std::cout << pixels[i] << " ";
        }
    }
};
