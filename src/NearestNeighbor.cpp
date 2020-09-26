//
// Created by va.morozov on 12.09.2020.
//

#include "NearestNeighbor.h"
#include <set>
#include <memory>
#include <iostream>

using namespace std;

namespace geometry {

namespace {

double distance(cluster& c1, cluster& c2)
{
    auto min_dist = numeric_limits<double>::infinity();
    for (auto& p1 : c1) {
        for (auto& p2 : c2) {
            min_dist = min(min_dist, dist(p1, p2));
        }
    }
    return min_dist;
}

cluster combine(cluster& c1, cluster& c2)
{
    cluster result = c1;
    result.insert(c2.begin(), c2.end());
    return result;
}

template<typename T>
void erase_from_unorderd_vector(std::vector<T>& vect, size_t i)
{
    swap(vect[i], vect.back());
    vect.pop_back();
}

} // anonymous

vector<cluster> NearestNeighbor(vector<Point>& points)
{
    vector<cluster> clusters, S, result;
    clusters.reserve(points.size());
    for (auto& p : points) {
        clusters.push_back({p});
    }
    while (S.size() + clusters.size() > 1) {
        if (S.empty()) {
            S.push_back(std::move(clusters.back()));
            clusters.pop_back();
        }
        int closestClusterId = -1;
        double closetClusterDistance = numeric_limits<double>::infinity();
        if (S.size() > 1) {
            closetClusterDistance = distance(S.back(), S[S.size() - 2]);
        }
        for (int i = 0; i < clusters.size(); ++i) {
            if (auto d = distance(S.back(), clusters[i]); d < closetClusterDistance) {
                closetClusterDistance = d;
                closestClusterId = i;
            }
        }
        if (closestClusterId == -1) {
            clusters.push_back(combine(S[S.size() - 2], S.back()));
            result.push_back(move(S.back()));
            S.pop_back();
            result.push_back(move(S.back()));
            S.pop_back();
        } else {
            S.push_back(move(clusters[closestClusterId]));
            erase_from_unorderd_vector(clusters, closestClusterId);
        }
    }
    result.push_back(move(clusters.back()));
    return result;
}

vector<cluster> stupidClustering(vector<Point>& points)
{
    vector<cluster> clusters, result;
    clusters.reserve(points.size());
    for (auto& p : points) {
        clusters.push_back({p});
    }
    int best_cluster1, best_cluster2;
    while (clusters.size() > 1) {
        auto best_dist = numeric_limits<double>::infinity();;
        for (int i = 0; i < clusters.size(); ++i) {
            for (int j = i + 1; j < clusters.size(); ++j) {
                if (auto d = distance(clusters[i], clusters[j]); d < best_dist) {
                    best_dist = d;
                    best_cluster1 = i;
                    best_cluster2 = j;
                }
            }
        }
        clusters.push_back(combine(clusters[best_cluster1], clusters[best_cluster2]));
        result.push_back(move(clusters[best_cluster1]));
        erase_from_unorderd_vector(clusters, best_cluster1);
        result.push_back(move(clusters[best_cluster2]));
        erase_from_unorderd_vector(clusters, best_cluster2);
    }
    result.push_back(move(clusters.back()));
    return result;
}

bool equal_clusters(vector<cluster> c1, vector<cluster> c2)
{
    sort(c1.begin(), c1.end());
    sort(c2.begin(), c2.end());
    return c1 == c2;
}

} // geometry