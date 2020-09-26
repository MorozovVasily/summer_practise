#include "Geometry.h"
#include "Sgn.h"
#include <cmath>

using namespace math;

namespace geometry {

Point::Point(coordinates x, coordinates y) : x(x), y(y) {}

Vector::Vector(Point p1, Point p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
}

Vector::Vector(coordinates x, coordinates y) : x(x), y(y) {}

Vector Point::operator- (const Point& p) const
{
    return Vector(p, *this);
}

bool Point::operator< (const Point& p) const
{
    if (x == p.x) {
        return y < p.y;
    }
    return x < p.x;
}

bool Point::operator== (const Point& p) const
{
    return x == p.x && y == p.y;
}

bool Vector::operator== (Vector p) const
{
    return x == p.x && y == p.y;
}

double Vector::length() const {
    return sqrt(x*x + y*y);
}

double vec(Vector v1, Vector v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

double scal(Vector v1, Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

double vec(Point p0, Point p1, Point p2) {
    return vec(p1 - p0, p2 - p0);
}

double vec(Point p0, Point p1, Vector v2) {
    return vec(p1 - p0, v2);
}

double vec(Vector v1, Point p0, Point p2) {
    return vec(v1, p2 - p0);
}

double scal(Point p0, Point p1, Point p2) {
    return scal(p1 - p0, p2 - p0);
}

double scal(Point p0, Point p1, Vector v2) {
    return scal(p1 - p0, v2);
}

double scal(Vector v1, Point p0, Point p2) {
    return scal(v1, p2 - p0);
}

double dist(Point p1, Point p2) {
    return (p1 - p2).length();
}

Sort_cmp::Sort_cmp(Point p) : p(p), v(0, 1) {}
Sort_cmp::Sort_cmp(Point p, Vector v) : p(p), v(v) {}

bool Sort_cmp::operator()(Point p1, Point p2)
{
    if (sgn(vec(p, p1, v)) != sgn(vec(p, p2, v))) {
        if (sgn(vec(p, p1, v)) == -1 || sgn(vec(p, p2, v)) == 1) {
            return true;
        }
        return false;
    }
    if (sgn(vec(p, p1, v)) == 0) {
        return (p1 - p).length() < (p2 - p).length();
    }
    return vec(p, p1, p2) < 0;
}

}