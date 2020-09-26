#pragma once

namespace geometry {

using coordinates = double;

struct Vector;

struct Point
{
    coordinates x, y;

    Point(coordinates x, coordinates y);

    Vector operator- (const Point&) const;
    bool operator< (const Point&) const;
    bool operator== (const Point&) const;
};

struct Vector
{
    coordinates x, y;

    Vector(Point p1, Point p2);
    Vector(coordinates x, coordinates y);

    double length() const;

    bool operator== (Vector p) const;
};

// Векторное произведение
double vec(Vector v1, Vector v2);
double vec(Point p0, Point p1, Point p2);
double vec(Point p0, Point p1, Vector v2);
double vec(Vector v1, Point p0, Point p2);
// Скалярное произведение
double scal(Vector v1, Vector v2);
double scal(Point p0, Point p1, Point p2);
double scal(Point p0, Point p1, Vector v2);
double scal(Vector v1, Point p0, Point p2);

double dist(Point p1, Point p2);

class Sort_cmp
{
    Point p;
    Vector v;
public:
    Sort_cmp(Point p);
    Sort_cmp(Point p, Vector v);
    bool operator()(Point p1, Point p2);
};

} //namespace geometry

