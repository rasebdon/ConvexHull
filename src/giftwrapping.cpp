#include "giftwrapping.h"

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
    for (int i = 1; i < n; ++i) {
        if (points[i].x < points[startPoint].x)
            startPoint = i;
    }

    int current = startPoint;
    do {
        convexHull.push_back(points[current]);
        int next = (current + 1) % n;
        
        for (int i = 0; i < n; ++i) {
            // Wenn der i-te Punkt links von der Linie zwischen current und next liegt
            if (Vector2::crossProduct(points[current], points[next], points[i]) > 0) {
                next = i;
            }
        }
        
        current = next;
    } while (current != startPoint);
    
    return convexHull;
}
