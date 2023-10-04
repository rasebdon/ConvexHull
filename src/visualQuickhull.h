#pragma once
#include "visualAlgorithm.h"
#include "giftwrapping.h"

class visualQuickhull : public visualAlgorithm
{
public:
    virtual std::vector<std::vector<Line>> Execute(const std::vector<Vector2>& points) const override;
    int crossProductSign(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3) const;
    double distanceToLine(const Vector2 &p, const Line &line) const;
    void quickHull(const std::vector<Vector2> &points, const Line &line, std::vector<Vector2> &convexHull, std::vector<Line>& testLines, std::vector<Line>& hullLines) const;
    bool isPointInConvexHull(const std::vector<Vector2> &convexHull, const Vector2 &point) const;
    bool isLineInConvexHull(const Line &line, const std::vector<Vector2> &convexHull) const;
};