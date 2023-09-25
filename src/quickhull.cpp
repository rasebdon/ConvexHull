#include "quickhull.h"
#include <math.h>

std::string quickhull::getName() const
{
    return "quickhull";
}

std::vector<Vector2> quickhull::Execute(const std::vector<Vector2> &points) const
{
    if (points.size() < 3) {
        return points;
    }

    std::vector<Vector2> convexHull;
    // Find the initial leftmost and rightmost points
    int min_x = 0, max_x = 0;
    for (size_t i = 1; i < points.size(); i++) {
        if (points[i].x < points[min_x].x)
            min_x = i;
        if (points[i].x > points[max_x].x)
            max_x = i;
    }

    // Compute the convex hull using the QuickHull algorithm
    this->quickHull(points, points[min_x], points[max_x], convexHull);

    return convexHull;
}

double quickhull::findDistance(Vector2 p1, Vector2 p2, Vector2 p) const
{
    double numerator = std::abs((p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x));
    double denominator = std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
    return numerator / denominator;
}

void quickhull::quickHull(const std::vector<Vector2> &points, Vector2 p1, Vector2 p2, std::vector<Vector2> &result) const
{
    int index = -1;
    double maxDistance = 0.0;

    for (size_t i = 0; i < points.size(); i++) {
        double distance = findDistance(p1, p2, points[i]);
        if (distance > maxDistance) {
            maxDistance = distance;
            index = i;
        }
    }

    if (index == -1) {
        result.push_back(p1);
        result.push_back(p2);
        return;
    }

    Vector2 A = points[index];
    std::vector<Vector2> leftSet, rightSet;

    for (size_t i = 0; i < points.size(); i++) {
        if (findDistance(p1, A, points[i]) > 0)
            leftSet.push_back(points[i]);
        else if (findDistance(A, p2, points[i]) > 0)
            rightSet.push_back(points[i]);
    }

    quickHull(leftSet, p1, A, result);
    quickHull(rightSet, A, p2, result);
}
