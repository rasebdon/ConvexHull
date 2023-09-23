#include <iostream>
#include "renderer.h"
#include "inputEventHandler.h"
#include "geometry.h"
#include "dataImporter.h"

#include "giftwrapping.h"
#include "quickhull.h"
#include "visualGiftwrapping.h"
#include "visualQuickhull.h"

#include "programOptions.h"

void performanceTestAlgorithm(const std::vector<Vector2>& points, algorithm& algo);
void renderAlgorithm(
    const Renderer& renderer,
    InputEventHandler& inputEventHandler,
    const std::vector<Vector2>& points,
    visualAlgorithm& visualAlgorithm);

int main(int argc, char **argv)
{
    programOptions options = programOptions(argc, argv);

    auto type = options.getArg("-type");
    auto algorithmType = options.getArg("-algo");

    // Setup rendering and input handler
    Renderer renderer = Renderer(800, 800);
    InputEventHandler inputEventHandler = InputEventHandler();

    // Import or generate points
    std::vector<Vector2> points;

    // TODO: Import points command line option

    srand (static_cast <unsigned> (time(0)));
    for (size_t i = 0; i < 15; i++)
    {
        float x = (float)rand() / (float)(RAND_MAX / renderer.getWindowSize().x);
        float y = (float)rand() / (float)(RAND_MAX / renderer.getWindowSize().y);
        points.push_back(Vector2 { x, y });
    }

    // Start algorithm in visual or performance mode
    if (type == "visual")
    {
        if (algorithmType == "giftwrapping")
        {
            visualGiftwrapping visualGift = visualGiftwrapping();
            renderAlgorithm(renderer, inputEventHandler, points, visualGift);
        }
        else if (algorithmType == "quickhull")
        {
            visualQuickhull visualQuick = visualQuickhull();
            renderAlgorithm(renderer, inputEventHandler, points, visualQuick);
        }
        else 
        {
            std::cerr << "Invalid algorithm provided! Options are \"giftwrapping\" and \"quickhull\"" << std::endl;
        }
    }
    else if (type == "performance")
    {
        if (algorithmType == "giftwrapping")
        {
            giftwrapping gift = giftwrapping();
            performanceTestAlgorithm(points, gift);
        }
        else if (algorithmType == "quickhull")
        {
            quickhull quick = quickhull();
            performanceTestAlgorithm(points, quick);
        }
        else 
        {
            std::cerr << "Invalid algorithm provided! Options are \"giftwrapping\" and \"quickhull\"" << std::endl;
        }
    }
    else 
    {
        std::cerr << "Invalid run type provided! Options are \"performance\" and \"visual\"" << std::endl;
    }

    return 0;
}

void performanceTestAlgorithm(const std::vector<Vector2>& points, algorithm& algo)
{

}

void renderAlgorithm(
    const Renderer& renderer,
    InputEventHandler& inputEventHandler,
    const std::vector<Vector2>& points,
    visualAlgorithm& visualAlgorithm)
{
    int i = 0;
    int drawNumber = -1;
    int list = 0;
    int listSize = 0;

    std::vector<std::vector<Line>> lineList = visualAlgorithm.Execute(points);

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
}