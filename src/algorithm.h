#pragma once
#include <vector>
#include "geometry.h"
#include "renderer.h"

class algorithm
{
public:
    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) = 0;
    virtual std::vector<std::vector<Line>> ExecuteVisual(const std::vector<Vector2>& points) = 0;
};