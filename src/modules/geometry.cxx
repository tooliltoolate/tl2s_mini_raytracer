module;


export module Geometry;

export struct Vector_2d
{
    double x, y;
    Vector_2d () = default;
    Vector_2d(double x, double y) : x(x), y(y) {}

} Vector_2d, Point;

export struct Vector_3d : Vector_2d
{
    double z;
    Vector_3d(double x, double y, double z) : z(z) { x = x; y = y;}
    Vector_3d(Vector_2d v, double z) : z(z) { x = v.x; y = v.y; }
};

export struct Ray
{
    Point origin;
    Vector_2d velocity;

    Ray(Point origin, Vector_2d velocity) : origin(origin), velocity(velocity) {}
    Point at(double t) const { return Point(origin.x + t * velocity.x, origin.y + t * velocity.y); }
};
