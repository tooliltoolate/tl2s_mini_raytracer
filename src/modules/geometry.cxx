module;

export module Geometry;

export class Vector_2d
{
public:
    double x_component, y_component;
    Vector_2d(double x, double y) : x_component(x), y_component(y) {}

};

export class Point
{
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

export class Ray
{
public:
    Point origin;
    Vector_2d velocity;

    Ray(Point origin, Vector_2d velocity) : origin(origin), velocity(velocity) {}
    Point at(double t) const { return Point(origin.x + t * velocity.x_component, origin.y + t * velocity.y_component); }
};
