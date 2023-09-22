#pragma once
#include "algorithm.h"

class quickhull : public algorithm
{
public:
    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) override;
    virtual std::vector<std::vector<Line>> ExecuteVisual(const std::vector<Vector2>& points) override;
};