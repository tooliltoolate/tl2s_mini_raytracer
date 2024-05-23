module;

export module Geometry;

export class Vector_2d
{
public:
    double x, y;
    Vector_2d(double x, double y) : x(x), y(y) {}

};

export typedef Vector_2d Point;

export class Ray
{
public:
    Point origin;
    Vector_2d velocity;

    Ray(Point origin, Vector_2d velocity) : origin(origin), velocity(velocity) {}
    Point at(double t) const { return Point(origin.x + t * velocity.x, origin.y + t * velocity.y); }
};
