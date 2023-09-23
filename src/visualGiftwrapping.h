#pragma once
#include "visualAlgorithm.h"


class visualGiftwrapping : public visualAlgorithm
{
private:
    Renderer &renderer;
public:
    visualGiftwrapping(Renderer &renderer);
    ~visualGiftwrapping();

    virtual std::vector<std::vector<Line>> Execute(const std::vector<Vector2>& points) override;
};