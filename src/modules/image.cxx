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

export template<typename T>
concept Numerical = std::integral<T> || std::floating_point<T>;

export enum Image_format
{
    PBM = 1,
    PGM = 2,
    PPM = 3
};

export template<Numerical Value_type, std::unsigned_integral auto Dimensions>
struct Pixel
{
    std::vector<Value_type> values{};
    constexpr static auto dimensions = Dimensions;

    friend std::istream& operator>>(std::istream& is, Pixel<Value_type, Dimensions>& pixel)
    {
        for (int i = 0; i < Dimensions; i++)
            is >> pixel.values[i];
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Pixel<Value_type, Dimensions>& pixel)
    {
        for (int i = 0; i < Dimensions; i++)
            os << +(pixel.values[i]) << " ";
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pixel<Value_type, Dimensions>& pixel)
    {
        for (int i = 0; i < Dimensions; i++)
            os << +(pixel.values[i]) << " ";
        return os;
    }
};

export template<Numerical Value_type, std::unsigned_integral auto channels>
struct Image
{
    unsigned int width{};
    unsigned int height{};
    unsigned int max_value{};
    std::vector<Pixel<Value_type, channels>> pixels{};

    unsigned int
    get_width() const
    {
        return width;
    }

    unsigned int
    get_height() const
    {
        return height;
    }

    void
    read_png(std::string filename)
    {
        std::vector<unsigned char> image;
        unsigned int error = lodepng::decode(image, width, height, filename, LCT_RGB, 8);
        if (error)
            throw std::runtime_error("decoder error " + std::to_string(error) + ": " + lodepng_error_text(error));

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

    template<Image_format filetype>
    void
    save_as_file(std::string path) const
    {
        std::filesystem::path p = path;
        std::ofstream file(path);
        if (!file.is_open()){
            throw std::runtime_error("Could not open file " + path);
        }
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
};
