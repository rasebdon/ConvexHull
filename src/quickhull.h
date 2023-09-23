#pragma once
#include "algorithm.h"

class quickhull : public algorithm
{
public:
    virtual std::string getName() const override;
    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) const override;
};