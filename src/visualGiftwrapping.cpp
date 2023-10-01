#include "visualGiftwrapping.h"
#include <cmath>

std::vector<std::vector<Line>> visualGiftwrapping::Execute(const std::vector<Vector2> &points) const
{
    std::vector<Line> testLines;
    std::vector<Line> hullLines;
    std::vector<std::vector<Line>> lineList;

    int n = points.size();

    std::vector<Vector2> convexHull;

    // Finden des Startpunktes
    int startPoint = 0;
    for (int i = 1; i < n; ++i) {
        if (points[i].x < points[startPoint].x)
            startPoint = i;
    }

    int current = startPoint;
    do {
        convexHull.push_back(points[current]);
        int next = (current + 1) % n;
        
        for (int i = 0; i < n; ++i) {

            float cross = Vector2::crossProduct(points[current], points[next], points[i]);
            // Wenn der i-te Punkt links von der Linie zwischen current und next liegt
            Line line(points[current], points[i]);
            testLines.push_back(line);

            if (cross > 0.0000001f) //Richtung bestimmen mit > oder <
            {
                next = i;
            }
            else if (cross <= 0.0000001f && cross >= -0.0000001f)
            {
                // Wenn colinear: Punkt mit grüßerer Distanz
                double dist1 = std::hypot(points[i].x - points[current].x, points[i].y - points[current].y);
                double dist2 = std::hypot(points[next].x - points[current].x, points[next].y - points[current].y);
                if (dist1 > dist2)
                {
                    next = i;
                }
            }
        }

        Line line(points[current], points[next]);
        hullLines.push_back(line);
        current = next;
        lineList.push_back(testLines);
        testLines.clear();
    } while (current != startPoint);

    lineList.push_back(hullLines);

    return lineList;
}