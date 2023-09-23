#pragma once
#include "algorithm.h"

class quickhull : public algorithm
{
public:
    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) const override;
};