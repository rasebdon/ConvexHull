#pragma once
#include <vector>
#include "geometry.h"

class algorithm
{
public:
    virtual std::string getName() const = 0;
    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) const = 0;
};