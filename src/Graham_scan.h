#pragma once

#include <src/common/Geometry.h>
#include <vector>

namespace geometry {

std::vector<Point> Graham_scan(std::vector<Point> points);

bool checkConvex(std::vector<Point>& points, std::vector<Point>& convex);

}
