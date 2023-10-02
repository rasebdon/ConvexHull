#pragma once
#include "algorithm.h"

class quickhull : public algorithm
{
public:
    virtual std::string getName() const override;
    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) const override;

private:
    double distanceToLine(const Vector2& p, const Line& line) const;
    int crossProductSign(const Vector2& p1, const Vector2& p2, const Vector2& p3) const;
    void quickHull(const std::vector<Vector2> &points, const Line& line, std::vector<Vector2> &convexHull) const;
    bool isPointInConvexHull(const std::vector<Vector2> &convexHull, const Vector2& point) const;
};