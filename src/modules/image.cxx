//use lodepng, and (maybe do smth about the alpha channel)
module;

#include "../third_party/lodepng.h"
#include <vector>
#include <iostream>
#include <cstdint>
#include <string>
#include <filesystem>
#include <fstream>
#include <stdexcept>

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
    uint8_t  max_value;
    unsigned int width, height;

    Image() : max_value(255), width(16), height(16) {}

    Image(unsigned int width, unsigned int height, uint8_t max_value, const std::vector<Pixel>& pixels) : width(width), height(height), max_value(max_value), pixels(pixels) {}

    Image(unsigned int width, unsigned int height, uint8_t max_value, const std::vector<uint8_t>& pixels) : width(width), height(height), max_value(max_value) {
        this->pixels.reserve(pixels.size() / 3);
        for (int i = 0; i < pixels.size(); i += 3)
            this->pixels.push_back(Pixel(pixels[i], pixels[i + 1], pixels[i + 2]));
    
    }

    Image(int width, int height, int max_value) : width(width), height(height), max_value(max_value) {}

    unsigned int&
    get_width()
    {
        return width;
    }

    unsigned int&
    get_height()
    {
        return height;
    }

    void
    read_png(std::string filename)
    {
        std::vector<unsigned char> image;
        unsigned int w, h;
        unsigned int error = lodepng::decode(image, w, h, filename, LCT_RGB, 8);
        if (error)
            throw std::runtime_error("decoder error " + std::to_string(error) + ": " + lodepng_error_text(error));
        else{
            get_width() = w;
            get_height() = h;
            pixels.clear();
            pixels.reserve(width * height);
            for (int i = 0; i < width * height * 3; i += 3)
                pixels.push_back(Pixel(image[i], image[i + 1], image[i + 2]));
        }
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
    save_as_ppm(std::string path) const
    {
        std::filesystem::path p = path;
        std::ofstream ppm_file(path);
        if (ppm_file.is_open()){
        ppm_file  << "P3" << "\n" << std::to_string(width) << " " << std::to_string(height) << "\n" << std::to_string(max_value) << "\n";
            for (int i = 0; i < width * height; i++)
            {
                    ppm_file << pixels[i] << "\n";
            }
        }
        else
            throw std::runtime_error("Could not open file " + path);
    }
};
