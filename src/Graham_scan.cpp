#include "Graham_scan.h"
#include <algorithm>
#include <set>

namespace geometry {

std::vector<Point> Graham_scan(std::vector<Point> points) {
    if (points.empty()) {
        return points;
    }
    Point bottom_left = *std::min_element(points.begin(), points.end());
    std::sort(points.begin(), points.end(), Sort_cmp(bottom_left));
    std::vector<Point> stack;
    stack.push_back(bottom_left);
    for (const auto point : points) {
        while (stack.size() >= 2) {
            if (vec(stack[stack.size() - 2], stack.back(), point) < 0) {
                break;
            } else {
                stack.pop_back();
            }
        }
        stack.push_back(point);
    }
    while (vec(stack[stack.size() - 2], stack.back(), bottom_left) >= 0) {
        stack.pop_back();
    }
    return stack;
}

bool checkConvex(std::vector<Point>& points, std::vector<Point>& convex)
{
    double eps = 1e-6;

    std::set<Point> set_convex(points.begin(), points.end());
    for (int i = 0; i < convex.size() - 2; ++i) {
        if (vec(convex[i], convex[i+1], convex[i+2]) >= 0) {
            return false;
        }
    }
    if (vec(convex[convex.size() - 2], convex[convex.size() - 1], convex[0]) >= 0 ||
        vec(convex[convex.size() - 1], convex[0], convex[1]) >= 0) {
        return false;
    }

    for (auto& point : points) {
        if (set_convex.find(point) != set_convex.end()) {
            double sum = 0;
            for (int i = 0; i < convex.size() - 1; ++i) {
                sum += vec(point, convex[i], convex[i+1]);
            }
            sum += vec(point, convex.back(), convex[0]);
            if (abs(sum) < eps) {
                return false;
            }
        }
    }
    return true;
}
}