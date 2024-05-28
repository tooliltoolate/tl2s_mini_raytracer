module;

#include <vector>
#include <iostream>
#include <cstdint>
#include <string>

export module Image;

export class Pixel
{

    public:
    uint8_t r, g, b;

    Pixel() {}
    Pixel(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

    friend std::istream& operator>>(std::istream& is, Pixel& pixel)
    {
        is >> pixel.r >> pixel.g >> pixel.b;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Pixel& pixel)
    {
        os << std::to_string(pixel.r) << " " << std::to_string(pixel.g) << " " << std::to_string(pixel.b);
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel)
    {
        os << std::to_string(pixel.r) << " " << std::to_string(pixel.g) << " " << std::to_string(pixel.b);
        return os;
    }
};


export class Image
{
public:
    std::vector<Pixel> pixels;
    const uint8_t width, height, max_value;

    Image(int width, int height, int max_value, const std::vector<Pixel>& pixels) : width(width), height(height), max_value(max_value), pixels(pixels) {}
    Image(int width, int height, int max_value, const std::vector<uint8_t>& pixels) : width(width), height(height), max_value(max_value) {
        this->pixels.reserve(pixels.size() / 3);
        for (int i = 0; i < pixels.size(); i += 3)
            this->pixels.push_back(Pixel(pixels[i], pixels[i + 1], pixels[i + 2]));
    
    }

    Image(int width, int height, int max_value) : width(width), height(height), max_value(max_value) {}

    void
    read_pixels()
    {
        for (int i = 0; i < width * height * 3; i++)
            std::cin >> pixels[i];
    }

    void
    set_pixels(const std::vector<Pixel>& pixels)
    {
        this->pixels = pixels;
    }

    void
    set_pixels(const std::vector<uint8_t>& pixels)
    {
        this->pixels.clear();
        this->pixels.reserve(pixels.size() / 3);
        for (int i = 0; i < pixels.size(); i += 3)
            this->pixels.push_back(Pixel(pixels[i], pixels[i + 1], pixels[i + 2]));
    }

    void
    print_as_ppm() const
    {
        std::cout << "P3" << "\n" << std::to_string(width) << " " << std::to_string(height) << "\n" << std::to_string(max_value) << "\n";
            for (int i = 0; i < width * height; i++)
            {
                    std::cout << pixels[i] << "\n";
            }
    }
};
