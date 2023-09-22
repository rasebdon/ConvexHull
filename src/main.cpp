#include "renderer.h"
#include "inputEventHandler.h"
#include "geometry.h"

#include "example.h"

int main(int argc, char **argv)
{
    // Setup rendering and input handler
    Renderer renderer = Renderer(800, 800);
    InputEventHandler inputEventHandler = InputEventHandler();

    // Example usage class
    Example example(renderer);

    // Render loop
    while (!inputEventHandler.quit)
    {
        // Handle input events
        inputEventHandler.Handle();

        // Init frame
        renderer.LimitFramerate(2);
        renderer.Clear();

        // Draw here with renderer.DrawPointF or renderer.DrawLineF

        // Example of how the draw functions are used:
        example.RenderPointsAndLines();

        // Render the prepared frame
        renderer.Render();
    }

    return 0;
}