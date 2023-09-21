#include "example.h"
#include <ctime>
#include "dataImporter.h"
#include <iostream>

Example::Example(Renderer &renderer) : renderer(renderer)
{
    points_start_index = 0;
    points_end_index = 0;

    points = DataImporter::ImportPoints("points.txt");

    // srand (static_cast <unsigned> (time(0)));
    // for (size_t i = 0; i < 15; i++)
    // {
    //     float x = (float)rand() / (float)(RAND_MAX / renderer.getWindowSize().x);
    //     float y = (float)rand() / (float)(RAND_MAX / renderer.getWindowSize().y);
    //     points.push_back(Vector2 { x, y });
    // }
}

Example::~Example()
{
}

// IMPORTANT: Always use renderer with reference or pointer, else the renderer object gets copied and its deconstructor will be called
// at the end of the function! Therefore killing the program.
void Example::RenderPointsAndLines()
{
    for (std::vector<Vector2>::const_iterator i = points.begin(); i != points.end(); ++i)
    {
        Vector2 point = *i;
        renderer.DrawPointF(point, 5, Color::Black()); // Example for point drawing
    }

    if (points_end_index < points.size() - 1)
    {
        points_end_index++;
    }
    else if (points_end_index == points.size() - 1)
    {
        points_end_index = ++points_start_index + 1;
    }

    if (points_start_index < points.size())
    {
        auto p_s = points[points_start_index];
        auto p_e = points[points_end_index];
        Line line(p_s, p_e);

        lines.push_back(line);
    }

    for (std::vector<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
    {
        Line line = *i;
        renderer.DrawLineF(line, 2, Color::Red()); // Example for line drawing
    }
}
