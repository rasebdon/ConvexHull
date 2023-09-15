#include <SDL.h>
#include <vector>
#include <ctime>
#include "./geometry.h"

int DrawPointF(SDL_Renderer *renderer, float x, float y, float pt);
int DrawPointF(SDL_Renderer *renderer, Vector2 position, float pt);
int DrawLineF(SDL_Renderer *renderer, float x1, float y1, float x2, float y2, float pt);
int DrawLineF(SDL_Renderer *renderer, Line line, float pt);

size_t p_s_index = 0;
size_t p_e_index = 0;

int main(int argc, char **argv)
{
    // variables

    bool quit = false;
    SDL_Event event;

    std::vector<Line> lines;
    std::vector<Vector2> points;

    srand (static_cast <unsigned> (time(0)));
    for (size_t i = 0; i < 15; i++)
    {
        float x = (float)rand() / (float)(RAND_MAX / 800);
        float y = (float)rand() / (float)(RAND_MAX / 800);
        points.push_back(Vector2 { x, y });
    }
    
    // init SDL

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("SDL2 line drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // handle events

    while (!quit)
    {
        SDL_Delay(250);
        SDL_PollEvent(&event);

        // Input

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }

        // Clear window

        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        // Draw
                
        for (std::vector<Vector2>::const_iterator i = points.begin(); i != points.end(); ++i)
        {
            Vector2 point = *i;
            DrawPointF(renderer, point, 5);
        }

        if (p_e_index < points.size())
        {
            p_e_index++;
        }
        else if (p_e_index == points.size())
        {
            p_s_index++;
            p_e_index = p_s_index + 1;
        }

        if (p_s_index < points.size())
        {
            auto p_s = points[p_s_index];
            auto p_e = points[p_e_index];
            lines.push_back(Line { p_s, p_e });
        }

        for (std::vector<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
        {
            Line line = *i;
            DrawLineF(renderer, line, 2);
        }

        // Render window

        SDL_RenderPresent(renderer);
    }

    // cleanup SDL

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int DrawPointF(SDL_Renderer *renderer, Vector2 position, float pt) 
{
    return DrawPointF(renderer, position.x, position.y, pt);
}

int DrawPointF(SDL_Renderer *renderer, float x, float y, float pt)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderSetScale( renderer, pt, pt);
    SDL_RenderDrawPointF(renderer, x/pt, y/pt);
    SDL_RenderSetScale( renderer, 1, 1);
    return 0;
}

int DrawLineF(SDL_Renderer *renderer, Line line, float pt)
{
    return DrawLineF(renderer, line.start.x, line.start.y, line.end.x, line.end.y, pt);
}

int DrawLineF(SDL_Renderer *renderer, float x1, float y1, float x2, float y2, float pt)
{
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
    SDL_RenderSetScale( renderer, pt, pt);
    SDL_RenderDrawLineF(renderer, x1/pt, y1/pt, x2/pt, y2/pt);
    SDL_RenderSetScale( renderer, 1, 1);
    return 0;
}