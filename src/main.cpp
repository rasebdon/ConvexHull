#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>

#include "renderer.h"
#include "inputEventHandler.h"
#include "geometry.h"
#include "dataImporter.h"

#include "giftwrapping.h"
#include "quickhull.h"
#include "visualGiftwrapping.h"
#include "visualQuickhull.h"

#include "programOptions.h"

void performanceTestAlgorithm(const std::vector<Vector2> &points, const algorithm &algo);
void renderAlgorithm(
    const Renderer &renderer,
    InputEventHandler &inputEventHandler,
    const std::vector<Vector2> &points,
    const visualAlgorithm &visualAlgorithm);
std::vector<Vector2> getPoints(const programOptions& options, const Renderer* renderer = nullptr);
std::string thousandSeperator(long long num);

int main(int argc, char **argv)
{
    programOptions options = programOptions(argc, argv);

    if (options.hasArg("-h") || options.hasArg("-?"))
    {
        std::cout << "Usage: convexHull.exe --type [performance | visual] --algo [giftwrapping | quickhull] [--import [path]] [--points [amount]]" << std::endl;
        return 0;
    }

    std::string type = options.getArg("--type");
    bool isVisual = type == "visual";
    if (type != "performance" && type != "visual")
    {
        std::cerr << "Invalid run type provided! Options are \"performance\" and \"visual\"" << std::endl;
    }

    std::string algorithmType = options.getArg("--algo");
    if (algorithmType != "giftwrapping" && algorithmType != "quickhull")
    {
        std::cerr << "Invalid algorithm provided! Options are \"giftwrapping\" and \"quickhull\"" << std::endl;
        return 1;
    }

    // Start algorithm in visual or performance mode
    if (isVisual)
    {
        // Setup rendering and input handler
        Renderer renderer = Renderer(800, 800);
        InputEventHandler inputEventHandler = InputEventHandler();

        // Create algorithm
        std::unique_ptr<visualAlgorithm> visualAlgo;
        if (algorithmType == "giftwrapping")
            visualAlgo = std::make_unique<visualGiftwrapping>();
        else if (algorithmType == "quickhull")
            visualAlgo = std::make_unique<visualQuickhull>();

        renderAlgorithm(renderer, inputEventHandler, getPoints(options, &renderer), *visualAlgo);
    }
    else
    {        
        // Create algorithm
        std::unique_ptr<algorithm> algo;
        if (algorithmType == "giftwrapping")
            algo = std::make_unique<giftwrapping>();
        else if (algorithmType == "quickhull")
            algo = std::make_unique<quickhull>();

        performanceTestAlgorithm(getPoints(options), *algo);
    }

    return 0;
}

std::vector<Vector2> getPoints(const programOptions& options, const Renderer* renderer)
{
    // Import or generate points
    std::vector<Vector2> points;

    if (options.hasArg("--import"))
    {
        points = DataImporter::ImportPoints(options.getArg("--import"));
    }
    else
    {
        size_t amount = 10;
        if (options.hasArg("--points"))
            amount = std::stoull(options.getArg("--points"));

        Vector2 bounds = Vector2(1000, 1000);        
        if (renderer != nullptr)
            bounds = renderer->getWindowSize();

        srand(static_cast<unsigned>(time(0)));
        for (size_t i = 0; i < amount; i++)
        {
            float x = (float)rand() / (float)(RAND_MAX / bounds.x);
            float y = (float)rand() / (float)(RAND_MAX / bounds.y);
            points.push_back(Vector2{x, y});
        }
    }
    
    return points;
}

void performanceTestAlgorithm(const std::vector<Vector2> &points, const algorithm &algo)
{
    std::vector<Vector2> hull;
    
    auto start = std::chrono::high_resolution_clock::now();
    hull = algo.Execute(points);
    auto finish = std::chrono::high_resolution_clock::now();

    std::cout << "Calculated convex hull of " << points.size() << " points with " << algo.getName() << ":" << std::endl;
    for (auto point : hull)
    {
        std::cout << point.toString() << std::endl;
    }

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    std::cout << "Calculation time: " << thousandSeperator(microseconds.count()) << " microseconds" << std::endl;

    // Write result to file
    std::string fileName = "results.csv";
    std::ifstream resultsInput(fileName);
    bool exists = resultsInput.good() && resultsInput.peek() != std::ifstream::traits_type::eof();

    std::ofstream file;
    file.open(fileName, std::ios::app);

    if (!exists)
        file << "algo,n,ms" << std::endl;
    file << algo.getName() << "," << points.size() << "," << microseconds.count() << std::endl; 
}

std::string thousandSeperator(long long n)
{
	std::string result = std::to_string(n);
	if (result.length() > 3)
	{
		for (int i = result.length() - 3; i > 0; i -= 3)
		{
			result.insert(i, ".");
		}
	}
	return result;
}

void renderAlgorithm(
    const Renderer &renderer,
    InputEventHandler &inputEventHandler,
    const std::vector<Vector2> &points,
    const visualAlgorithm &visualAlgorithm)
{
    int i = 0;
    int drawNumber = -1;
    int list = 0;
    int listSize = 0;

    std::vector<std::vector<Line>> lineList = visualAlgorithm.Execute(points);

    int size = lineList.size();

    std::vector<Line> testLines = lineList[list];
    listSize = testLines.size() - 1;
    std::vector<Line> hullLines = lineList[size - 1];

    // Render loop
    while (!inputEventHandler.quit)
    {
        // Handle input events
        inputEventHandler.Handle();

        // Init frame
        renderer.LimitFramerate(5);
        renderer.Clear();

        // Draw here with renderer.DrawPointF or renderer.DrawLineF
        for (std::vector<Vector2>::const_iterator i = points.begin(); i != points.end(); ++i)
        {
            Vector2 point = *i;
            renderer.DrawPointF(point, 5, Color::Black());
        }

        for (int j = 0; j <= drawNumber; j++)
        {
            renderer.DrawLineF(hullLines[j], 2, Color::Red());
        }

        if (drawNumber <= ((int)hullLines.size()))
        {
            for (int k = 0; k <= i; k++)
            {
                renderer.DrawLineF(testLines[k], 2, Color::Blue());
            }

            if (inputEventHandler.keyboard[SDL_KeyCode::SDLK_RIGHT])
            {
                if (i >= listSize)
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
            }
        }

        // Render the prepared frame
        renderer.Render();
    }
}