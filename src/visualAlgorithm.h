#pragma once
#include <vector>
#include "geometry.h"
#include "renderer.h"

class visualAlgorithm
{
public:
    virtual std::vector<std::vector<Line>> Execute(const std::vector<Vector2>& points) = 0;
};