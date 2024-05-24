module;

#include <cstdint>
#include <vector>
#include <iostream>

export module Image;

export class Pixel
{
    uint8_t r, g, b;

    public:
    Pixel() : r(0), g(0), b(0) {}
    Pixel(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    Pixel(uint8_t& r, uint8_t& g, uint8_t& b) : r(r), g(g), b(b) {}
    Pixel(Pixel& input) {}
    Pixel(const Pixel& input) {}

    friend std::istream& operator>>(std::istream& is, Pixel& pixel)
    {
        is >> pixel.r >> pixel.g >> pixel.b;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Pixel& pixel)
    {
        os << pixel.r << " " << pixel.g << " " << pixel.b;
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel)
    {
        os << pixel.r << " " << pixel.g << " " << pixel.b;
        return os;
    }
};


export class Image
{
    const uint8_t width, height, max_value;
    std::vector<Pixel> pixels;
public:

    Image(int width, int height, int max_value, const std::vector<Pixel>& pixels) : width(width), height(height), max_value(max_value), pixels(pixels) {}

    Image(int width, int height, int max_value) : width(width), height(height), max_value(max_value) {}

    void read_pixels()
    {
        for (int i = 0; i < width * height * 3; i++)
            std::cin >> pixels[i];
    }

    void set_pixels(const std::vector<Pixel>& pixels)
    {
        this->pixels = pixels;
    }

    void set_pixels(const std::vector<uint8_t>& pixels)
    {
        this->pixels.clear();
        this->pixels.reserve(pixels.size() / 3);
        for (int i = 0; i < pixels.size(); i += 3)
            this->pixels.push_back(Pixel(pixels[i], pixels[i + 1], pixels[i + 2]));
    }

    void print_as_ppm() const
    {
        std::cout << "P" << 3 << "\n" << width << " " << height << "\n" << max_value << "\n";
            for (int i = 0; i < width * height; i++)
            {
                    std::cout << pixels[i] << "\n";
            }
    }
};
