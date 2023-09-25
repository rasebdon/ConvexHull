#pragma once
#include "algorithm.h"

class quickhull : public algorithm
{
public:
    virtual std::string getName() const override;
    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) const override;

private:
    double findDistance(Vector2 p1, Vector2 p2, Vector2 p) const;
    void quickHull(const std::vector<Vector2> &points, Vector2 p1, Vector2 p2, std::vector<Vector2> &result) const;
};