module;

#include <valarray>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <concepts>

export module Geometry;

export template<typename T>
concept Numerical = std::integral<T> || std::floating_point<T>;

export template<Numerical Component_type, std::integral auto Dimensions>
struct Vector
{
    std::valarray<Component_type> components = std::valarray<Component_type>(Dimensions);
    constexpr static auto dimensions = Dimensions;
    Numerical auto& operator[](std::integral auto i){
        return components[i];
    }
    Vector<Component_type, Dimensions>& operator+(const Vector<Component_type, Dimensions>& v) const {
        return Vector<Component_type, Dimensions>(components + v.components);
    }
    Vector<Component_type, Dimensions>& operator*(const Vector<Component_type, Dimensions>& v) const {
        return Vector<Component_type, Dimensions>( components * v.components);
    }
    Vector<Component_type, Dimensions>& operator-(const Vector<Component_type, Dimensions>& v) const {
        return Vector<Component_type, Dimensions>( components - v.components);
    }
    Vector<Component_type, Dimensions>& operator*(Numerical auto t) const {
        return Vector<Component_type, Dimensions>( components * t);
    }
    Vector<Component_type, Dimensions>& operator/(Numerical auto t) const {
        return Vector<Component_type, Dimensions>( components / t);
    }
    bool operator==(const Vector<Component_type, Dimensions>& other) const {
        return components == other.components && dimensions == other.dimensions;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector<Component_type, Dimensions>& vector) {
        os << "Vector(";
        for (int i = 0; i < Dimensions; ++i) {
            os << vector.components[i] << ", ";
        }
        os << ")";
        return os;
    }
};

export template<Numerical Component_type>
using Vector_2d = Vector<Component_type, 2>;

export template<Numerical Component_type>
using Vector_3d = Vector<Component_type, 3>;

export template<Numerical Coordinate_type, std::integral auto Dimensions>
struct Point
{
    std::valarray<Coordinate_type> coordinates = std::valarray<Coordinate_type>(Dimensions);
    constexpr static auto dimensions = Dimensions;

    Numerical auto& operator[](std::integral auto i){
        return coordinates[i];
    }
    Point<Coordinate_type, Dimensions>& operator+(const Vector<Coordinate_type, Dimensions>& v) const {
        return Point<Coordinate_type, Dimensions>( coordinates + v.components);
    }
    Point<Coordinate_type, Dimensions>& operator*(const Vector<Coordinate_type, Dimensions>& v) const {
        return Point<Coordinate_type, Dimensions>( coordinates * v);
    }
    Point<Coordinate_type, Dimensions>& operator-(const Vector<Coordinate_type, Dimensions>& v) const {
        return Point<Coordinate_type, Dimensions>( coordinates - v.components);
    }
    Point<Coordinate_type, Dimensions>& operator*(Numerical auto t) const {
        return Point<Coordinate_type, Dimensions>( coordinates * t);
    }
    bool operator==(const Point<Coordinate_type, Dimensions>& other) const {
        return coordinates == other.coordinates && dimensions == other.dimensions;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point<Coordinate_type, Dimensions>& point) {
        os << "Point(";
        for (int i = 0; i < Dimensions; ++i) {
            os << point.coordinates[i] << ", ";
        }
        os << ")";
        return os;
    }
};

export template<Numerical Component_type>
using Point_2d = Point<Component_type, 2>;

export template<Numerical Component_type>
using Point_3d = Point<Component_type, 3>;

export template<Numerical Coordinate_type>
struct Ray
{
    Point_3d<Coordinate_type> origin;
    Vector_3d<Coordinate_type> velocity;

    Point_3d<Coordinate_type> at(Numerical auto t) const {
        return Point_3d<Coordinate_type>(origin.coordinates + velocity.components * t); 
    }
};
