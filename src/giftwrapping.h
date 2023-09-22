#pragma once
#include "algorithm.h"


class giftwrapping : public algorithm
{
private:
    Renderer &renderer;
public:
    giftwrapping(Renderer &renderer);
    ~giftwrapping();

    virtual std::vector<Vector2> Execute(const std::vector<Vector2>& points) override;
    virtual std::vector<std::vector<Line>> ExecuteVisual(const std::vector<Vector2>& points) override;
};