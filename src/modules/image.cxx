module;

#include <cstdint>
#include <vector>
#include <iostream>

export module Image;

export class Image
{
    const uint8_t channels, width, height, max_value;
    std::vector<uint8_t> pixels;
public:

    Image(int channels, int width, int height, int max_value) : channels(channels), width(width), height(height), max_value(max_value), pixels(width * height * channels) {}

    void read_pixels()
    {
        for (int i = 0; i < width * height * channels; i++)
            std::cin >> pixels[i];
    }

    void set_pixels(const std::vector<uint8_t>& pixels)
    {
        this->pixels = pixels;
    }

    void print_as_ppm() const
    {
        std::cout << "P" << channels << "\n" << width << " " << height << "\n" << max_value << "\n";
            for (int i = 0; i < width * height * channels; i++)
            {
                if ((i + 1) % channels == 0)
                    std::cout << pixels[i] << "\n";
                else
                    std::cout << pixels[i] << " ";
            }
    }
};
