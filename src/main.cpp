#include "renderer.h"
#include "inputEventHandler.h"
#include "geometry.h"
#include "dataImporter.h"
#include "visualGiftwrapping.h"
#include <iostream>

#include "example.h"

int main(int argc, char **argv)
{
    // Setup rendering and input handler
    Renderer renderer = Renderer(800, 800);
    InputEventHandler inputEventHandler = InputEventHandler();

    visualGiftwrapping gift(renderer);

    std::vector<Vector2> points;
    srand (static_cast <unsigned> (time(0)));
    for (size_t i = 0; i < 15; i++)
    {
        float x = (float)rand() / (float)(RAND_MAX / renderer.getWindowSize().x);
        float y = (float)rand() / (float)(RAND_MAX / renderer.getWindowSize().y);
        points.push_back(Vector2 { x, y });
    }

    int i = 0;
    int drawNumber = -1;
    int list = 0;
    int listSize = 0;

    std::vector<std::vector<Line>> lineList = gift.Execute(points);

    int size = lineList.size();

    std::vector<Line> testLines = lineList[list];
    listSize = testLines.size() - 1;
    std::vector<Line> hullLines = lineList[size-1];


    // Render loop
    while (!inputEventHandler.quit)
    {
        // Handle input events
        inputEventHandler.Handle();

        // Init frame
        renderer.LimitFramerate(4);
        renderer.Clear();

        // Draw here with renderer.DrawPointF or renderer.DrawLineF

        // Example of how the draw functions are used:
        //example.RenderPointsAndLines();
        for (std::vector<Vector2>::const_iterator i = points.begin(); i != points.end(); ++i)
        {
            Vector2 point = *i;
            renderer.DrawPointF(point, 5, Color::Black()); // Example for point drawing
        }

        for (int j = 0; j <= drawNumber; j++)
        {
            renderer.DrawLineF(hullLines[j], 2, Color::Red());
        }

        for(int k = 0; k <= i; k++)
        {
            renderer.DrawLineF(testLines[k], 2, Color::Blue());
        }

        if(i >= listSize)
        {
            i = 0;
            drawNumber++;
            testLines = lineList[++list];
            listSize = testLines.size() - 1;
        }
        else
        {
            i++;
        }

        // Render the prepared frame
        renderer.Render();
    }

    return 0;
}