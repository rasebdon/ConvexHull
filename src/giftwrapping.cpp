#include "giftwrapping.h"
#include <cmath>

std::string giftwrapping::getName() const
{
    return "giftwrapping";
}


std::vector<Vector2> giftwrapping::Execute(const std::vector<Vector2> &points) const
{
    int n = points.size();

    std::vector<Vector2> convexHull;

    // Finden des Startpunktes
    int startPoint = 0;
    for (int i = 1; i < n; ++i)
    {
        if (points[i].x < points[startPoint].x)
            startPoint = i;
    }

    int current = startPoint;
    do
    {
        convexHull.push_back(points[current]);
        int next = (current + 1) % n;
        
        for (int i = 0; i < n; ++i)
        {
            float cross = Vector2::crossProduct(points[current], points[next], points[i]);
            // Wenn der i-te Punkt rechts von der Linie zwischen current und next liegt
            if (cross > 0.0000001f) //Richtung bestimmen mit > oder <
            {
                next = i;
            }
            else if (cross > -0.0000001f)
            {
                // Wenn colinear: Punkt mit größerer Distanz
                if((points[i].x > points[next].x && points[i].y > points[next].y) || (points[i].x > points[next].x && points[i].y < points[next].y) || (points[i].x < points[next].x && points[i].y > points[next].y) || (points[i].x < points[next].x && points[i].y < points[next].y))
                {
                    double dist1 = std::hypot(points[i].x - points[current].x, points[i].y - points[current].y);
                    double dist2 = std::hypot(points[next].x - points[current].x, points[next].y - points[current].y);
                    if (dist1 > dist2)
                    {
                        next = i;
                    }
                }
            }
        }
        
        current = next;
    } while (current != startPoint);

    return convexHull;
}
