module;

#include <vector>
#include <cstdint>

template<typename T>
concept Numerical = std::integral<T> || std::floating_point<T>;

export module Geometry;

export template<Numerical Component_type, std::integral auto Dimensions>
struct Vector
{
    std::vector<Component_type> components{};
    constexpr static auto dimensions = Dimensions;
};

export template<Numerical Component_type>
using Vector_2d = Vector<Component_type, (uint8_t)2>;

export template<Numerical Component_type>
using Vector_3d = Vector<Component_type, (uint8_t)3>;

export template<Numerical Coordinate_type, std::integral auto Dimensions>
struct Point
{
    std::vector<Coordinate_type> coordinates{};
    constexpr static auto dimensions = Dimensions;
};

export template<Numerical Component_type>
using Point_2d = Point<Component_type, (uint8_t)2>;

export template<Numerical Component_type>
using Point_3d = Point<Component_type, (uint8_t)3>;

export template<Numerical Coordinate_type>
struct Ray
{
    Point_3d<Coordinate_type> origin;
    Vector_3d<Coordinate_type> velocity;

    Point_3d<Coordinate_type> at(Numerical auto t) const {
        return Point_3d<Coordinate_type>{ .coordinates = origin.coordinates + velocity.components * t, .dimensions = (uint8_t)3}; 
    }
};
