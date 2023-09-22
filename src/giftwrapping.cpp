#include "giftwrapping.h"
#include <iostream>

giftwrapping::giftwrapping(Renderer &renderer) : renderer(renderer)
{

}

giftwrapping::~giftwrapping()
{
    
}


int crossProduct(const Vector2& A, const Vector2& B, const Vector2& C)
{
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

std::vector<Vector2> giftwrapping::Execute(const std::vector<Vector2> &points)
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
            if (crossProduct(points[current], points[next], points[i]) > 0) {
                next = i;
            }
        }
        
        current = next;
    } while (current != startPoint);
    
    return convexHull;
}

std::vector<std::vector<Line>> giftwrapping::ExecuteVisual(const std::vector<Vector2> &points)
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
            // Wenn der i-te Punkt links von der Linie zwischen current und next liegt
            Line line(points[current], points[i]);
            testLines.push_back(line);
            if (crossProduct(points[current], points[next], points[i]) > 0) {
                next = i;
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