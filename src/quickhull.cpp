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
    if (points.size() < 3)
    {
        return points;
    }

    std::vector<Vector2> convexHull;
    // Find the initial leftmost and rightmost points
    Vector2 minX = points[0], maxX = points[0];
    for (size_t i = 1; i < points.size(); i++)
    {
        if (points[i].x < minX.x)
            minX = points[i];
        if (points[i].x > maxX.x)
            maxX = points[i];
    }

    convexHull.push_back(minX);
    convexHull.push_back(maxX);

    // Teilen der Punkte in zwei Hälften
    std::vector<Vector2> leftSet, rightSet;
    for (size_t i = 0; i < points.size(); i++)
    {
        int sign = crossProductSign(minX, maxX, points[i]);
        if (sign > 0)
            leftSet.push_back(points[i]);
        else if (sign < 0)
            rightSet.push_back(points[i]);
    }

    Line dividingLine = Line(minX, maxX);
    quickHull(leftSet, dividingLine, convexHull);
    quickHull(rightSet, dividingLine, convexHull);

    /*
    for(auto p : convexHull){
        cout << p.x << " " << p.y << endl;
    }
    */

    return convexHull;
}

int quickhull::crossProductSign(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3) const
{
    double crossProduct = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    return (crossProduct > 0) ? 1 : ((crossProduct < 0) ? -1 : 0);
}

double quickhull::distanceToLine(const Vector2 &p, const Line &line) const
{
    double a = line.start.y - line.end.y;
    double b = line.end.x - line.start.x;
    double c = line.start.x * line.end.y - line.end.x * line.start.y;

    return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
}

void quickhull::quickHull(const std::vector<Vector2> &points, const Line &line, std::vector<Vector2> &convexHull) const
{
    int farthestIndex = -1;
    double maxDistance = 0.0;

    for (size_t i = 0; i < points.size(); i++)
    {
        double currentDistance = distanceToLine(points[i], line);
        if (currentDistance > maxDistance)
        {
            maxDistance = currentDistance;
            farthestIndex = i;
        }
    }

    if (farthestIndex == -1)
    {
        return;
    }

    Vector2 farthestPoint = points[farthestIndex];
    std::vector<Vector2> leftSet, rightSet;
    int preSign = crossProductSign(line.start, line.end, farthestPoint); // Gebraucht um zu sehen auf welcher seite der ursprungspunkt liegt

    for (size_t i = 0; i < points.size(); i++)
    {
        int sign = crossProductSign(line.start, farthestPoint, points[i]) * preSign;
        if (sign > 0)
            leftSet.push_back(points[i]);
    }

    // Rekursiver Aufruf für die linke Menge
    if (leftSet.size() > 0)
    {
        Line leftDivider = Line(line.start, farthestPoint);
        quickHull(leftSet, leftDivider, convexHull);
    }

    // Hinzufügen des am weitesten entfernten Punktes zur Hülle, falls er nicht bereits enthalten ist
    if (!isPointInConvexHull(convexHull, farthestPoint))
    {
        convexHull.push_back(farthestPoint);
    }

    // Rekursiver Aufruf für die rechte Menge
    for (size_t i = 0; i < points.size(); i++)
    {
        int sign = crossProductSign(farthestPoint, line.end, points[i]) * preSign;
        if (sign > 0)
            rightSet.push_back(points[i]);
    }

    if (rightSet.size() > 0)
    {
        Line rightDivider = Line(farthestPoint, line.end);
        quickHull(rightSet, rightDivider, convexHull);
    }
}

bool quickhull::isPointInConvexHull(const std::vector<Vector2> &convexHull, const Vector2 &point) const
{
    for (const Vector2 &p : convexHull)
    {
        if (p.x == point.x && p.y == point.y)
        {
            return true;
        }
    }
    return false;
}
