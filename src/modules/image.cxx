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

template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;

export module Image;

//shadows or smth
export template<Number Value_type, std::unsigned_integral auto _dimensions>
struct Pixel
{
    std::vector<Value_type> values{};
    constexpr static auto dimensions = _dimensions;

    friend std::istream& operator>>(std::istream& is, Pixel<Value_type, _dimensions>& pixel)
    {
        for (int i = 0; i < _dimensions; i++)
            is >> pixel.values[i];
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Pixel<Value_type, _dimensions>& pixel)
    {
        for (int i = 0; i < _dimensions; i++)
            os << +(pixel.values[i]) << " ";
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pixel<Value_type, _dimensions>& pixel)
    {
        for (int i = 0; i < _dimensions; i++)
            os << +(pixel.values[i]) << " ";
        return os;
    }
};

export template<Number Value_type, std::unsigned_integral auto channels>
struct Image
{
    unsigned int width{};
    unsigned int height{};
    unsigned int max_value{};
    std::vector<Pixel<Value_type, channels>> pixels{};

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
            for (int i = 0; i < width * height * channels; i+=channels){
                Pixel<Value_type, channels> p;
                for (int j = 0; j < channels; j++) {
                    p.values.push_back(image[i + j]);
                }
                pixels.push_back(p);
            }
        }
    }

    void
    set_pixels(const std::vector<Pixel<Value_type, channels>>& pixels)
    {
        this->pixels = pixels;
    }

    void
    set_pixels(const std::vector<uint8_t>& pixels)
    {
        this->pixels.clear();
        this->pixels.reserve((pixels.size() + channels) / channels);
        for (int i = 0; i < pixels.size(); i += channels){
            Pixel<Value_type, channels> p;
            for (int j = 0; j < channels; j++) {
                p.values.push_back(pixels[i + j]);
            }
            this->pixels.push_back(p);
        }
    }

    //1 for pbm, 2 for pgm, 3 for ppm
    template<uint8_t filetype>
    void
    save_as_file(std::string path) const
    {
        std::filesystem::path p = path;
        std::ofstream file(path);
        if (!file.is_open()){
            throw std::runtime_error("Could not open file " + path);
        }
        else {
            file << "P" << std::to_string(filetype) << std::endl;
            file << std::to_string(width) << " " << std::to_string(height) << std::endl;
            if constexpr (filetype > 1){
                file << std::to_string(max_value) << std::endl;
            }
            for (int i = 0; i < width * height; i++)
            {
                    file << pixels[i] << std::endl;
            }
        }
    }

    template<uint8_t filetype>
    void
    print_as_file() const
    {
        std::cout << "P" << std::to_string(filetype) << std::endl;
        std::cout << std::to_string(width) << " " << std::to_string(height) << std::endl;
        if constexpr (filetype > 1){
            std::cout << std::to_string(max_value) << std::endl;
        }
        for (int i = 0; i < width * height; i++)
        {
                std::cout << pixels[i] << "\n";
        }
    }
};
