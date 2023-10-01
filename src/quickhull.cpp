#include "quickhull.h"
#include <cmath>
#include <iostream>

using namespace std;

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
    Vector2 minX = points[0], maxX = points[0];
    for (int i = 1; i < points.size(); i++) {
        if (points[i].x < minX.x)
            minX = points[i];
        if (points[i].x > maxX.x)
            maxX = points[i];
    }

    convexHull.push_back(minX);
    convexHull.push_back(maxX);

    // Teilen der Punkte in zwei Hälften
    std::vector<Vector2> leftSet, rightSet;
        for (size_t i = 0; i < points.size(); i++) {
            int sign = crossProductSign(minX, maxX, points[i]);
            if (sign > 0)
                leftSet.push_back(points[i]);
            else if (sign < 0)
                rightSet.push_back(points[i]);
        }

    quickHull(leftSet, minX, maxX, convexHull);
    quickHull(rightSet, maxX, minX, convexHull);

    /*
    for(auto p : convexHull){
        cout << p.x << " " << p.y << endl;
    }
    */

    return convexHull;
}

int quickhull::crossProductSign(Vector2 p1, Vector2 p2, Vector2 p3) const {
    double crossProduct = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    return (crossProduct > 0) ? 1 : ((crossProduct < 0) ? -1 : 0);
}

double quickhull::distanceToLine(Vector2 p, Vector2 l1, Vector2 l2) const {
    double A = p.x - l1.x;
    double B = p.y - l1.y;
    double C = l2.x - l1.x;
    double D = l2.y - l1.y;

    double dotProduct = A * C + B * D;
    double len2 = C * C + D * D;
    
    return std::abs(dotProduct) / sqrt(len2);
}

void quickhull::quickHull(const std::vector<Vector2> &points, Vector2 p1, Vector2 p2, std::vector<Vector2> &convexHull) const
{
    int farthestIndex = -1;
    double maxDistance = 0.0;

    for (size_t i = 0; i < points.size(); i++) {
        double currentDistance = distanceToLine(points[i], p1, p2);
        if (currentDistance > maxDistance) {
            maxDistance = currentDistance;
            farthestIndex = i;
        }
    }

    if (farthestIndex == -1) {
        return;
    }

    Vector2 farthestPoint = points[farthestIndex];
        std::vector<Vector2> leftSet, rightSet;

        for (int i = 0; i < points.size(); i++) {
            int sign = crossProductSign(p1, farthestPoint, points[i]);
            if (sign > 0)
                leftSet.push_back(points[i]);
        }

        // Rekursiver Aufruf für die linke Menge
        quickHull(leftSet, p1, farthestPoint, convexHull);

        // Hinzufügen des am weitesten entfernten Punktes zur Hülle, falls er nicht bereits enthalten ist
        if (!isPointInConvexHull(convexHull, farthestPoint)) {
            convexHull.push_back(farthestPoint);
        }

        // Rekursiver Aufruf für die rechte Menge
        for (int i = 0; i < points.size(); i++) {
            int sign = crossProductSign(farthestPoint, p2, points[i]);
            if (sign > 0)
                rightSet.push_back(points[i]);
        }
        quickHull(rightSet, farthestPoint, p2, convexHull);
}

bool quickhull::isPointInConvexHull(const std::vector<Vector2> &convexHull, Vector2 point) const {
        for (const Vector2 &p : convexHull) {
            if (p.x == point.x && p.y == point.y) {
                return true;
            }
        }
        return false;
    }
