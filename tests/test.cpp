#include <random>
#include <iostream>

#include "src/Graham_scan.h"
#include "src/NearestNeighbor.h"

using namespace std;

using namespace geometry;

vector<Point> generate_points(size_t n) {
    auto seed = random_device()();
    mt19937 rng(seed);
    vector<Point> result;
    result.reserve(n);
    for (int i = 0; i < n; ++i) {
        result.emplace_back(rng() + rng() * 1. / std::mt19937::max(), rng() + rng() * 1. / std::mt19937::max());
    }
    return result;
}

void test_Graham(size_t n) {
    auto points = generate_points(n);
    auto convex = Graham_scan(points);
    assert(checkConvex(points, convex));
}

void test_NearestNeighbor(size_t n) {
    auto points = generate_points(n);
    auto clusters = NearestNeighbor(points);
    auto clusters2 = stupidClustering(points);
    assert(equal_clusters(clusters, clusters2));
}

void test() {
    mt19937 rng((random_device()()));
    for (int i = 0; i < 100; ++i) {
        auto n_points = rng() % 1000 + 3;
        test_Graham(n_points);
    }
    for (int i = 0; i < 100; ++i) {
        auto n_points = rng() % 100 + 3;
        test_NearestNeighbor(n_points);
    }
}

int main() {
    std::cout << "Tests started!\n";
    test();
    std::cout << "Tests completed!!!\n";
}
