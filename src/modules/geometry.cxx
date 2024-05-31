module;

#include <vector>
#include <cstdint>

template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;

export module Geometry;

export template<Number Component_type, std::unsigned_integral auto _dimensions>
struct Vector
{
    std::vector<Component_type> components{};
    constexpr static auto dimensions = _dimensions;
};

export template<Number Component_type>
using Vector_2d = Vector<Component_type, (uint8_t)2>;

export template<Number Component_type>
using Vector_3d = Vector<Component_type, (uint8_t)3>;

export template<Number Coordinate_type, std::unsigned_integral auto _dimensions>
struct Point
{
    std::vector<Coordinate_type> coordinates{};
    constexpr static auto dimensions = _dimensions;
};

export template<Number Component_type>
using Point_2d = Point<Component_type, (uint8_t)2>;

export template<Number Component_type>
using Point_3d = Point<Component_type, (uint8_t)3>;

export template<Number Coordinate_type>
struct Ray
{
    Point_3d<Coordinate_type> origin;
    Vector_3d<Coordinate_type> velocity;

    Point_3d<Coordinate_type> at(Number auto t) const {
        return Point_3d<Coordinate_type>{ .coordinates = origin.coordinates + velocity.components * t, .dimensions = (uint8_t)3}; 
    }
};
