#pragma once
#include "algorithm.h"

class quickhull : public algorithm
{
public:
    virtual std::string getName() const override;
    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) const override;

private:
    double distanceToLine(Vector2 p, Vector2 l1, Vector2 l2) const;
    int crossProductSign(Vector2 p1, Vector2 p2, Vector2 p3) const;
    void quickHull(const std::vector<Vector2> &points, Vector2 p1, Vector2 p2, std::vector<Vector2> &convexHull) const;
    bool isPointInConvexHull(const std::vector<Vector2> &convexHull, Vector2 point) const;
};