//
// Created by va.morozov on 12.09.2020.
//
#pragma once

#include <src/common/Geometry.h>
#include <vector>
#include <set>

namespace geometry {
using cluster = std::set<Point>;

std::vector<cluster> NearestNeighbor(std::vector<Point>& points);

std::vector<cluster> stupidClustering(std::vector<Point>& points);

bool equal_clusters(std::vector<cluster> c1, std::vector<cluster> c2);
}
