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
            int cross = Vector2::crossProduct(points[current], points[next], points[i]);
            // Wenn der i-te Punkt links von der Linie zwischen current und next liegt
            if (cross > 0) //Richtung bestimmen mit > oder <
            {
                next = i;
            }
            else if (cross == 0)
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
        
        current = next;
    } while (current != startPoint);

    //check for duplications
    std::vector<Vector2> uniquePoints;

    for (const Vector2& point : convexHull)
    {
        bool isDuplicate = false;

        // Check if the current point is a duplicate of any point in uniquePoints
        for (const Vector2& uniquePoint : uniquePoints)
        {
            if (point == uniquePoint) 
            {
                isDuplicate = true;
                break;
            }
        }

        // If it's not a duplicate, add it to uniquePoints
        if (!isDuplicate)
        {
            uniquePoints.push_back(point);
        }
    }

    return uniquePoints;
}
