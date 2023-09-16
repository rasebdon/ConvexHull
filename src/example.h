#pragma once
#include "renderer.h"
#include <vector>

class Example
{
    private:
        size_t points_start_index = 0;
        size_t points_end_index = 0;
        std::vector<Line> lines;
        std::vector<Vector2> points;

        Renderer &renderer;
    public:
        Example(Renderer &renderer);
        ~Example();

        // IMPORTANT: Always use renderer with reference or pointer, else the renderer object gets copied and its deconstructor will be called
        // at the end of the function! Therefore killing the program.
        void RenderPointsAndLines();
};