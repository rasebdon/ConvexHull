#include "renderer.h"

void Renderer::SetRenderDrawColor(Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Renderer::SetRenderScale(float scale)
{
    SDL_RenderSetScale(renderer, scale, scale);
}

Renderer::Renderer(size_t width, size_t height)
{
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow("Convex Hull", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    this->renderer = SDL_CreateRenderer(window, -1, 0);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Vector2 Renderer::getWindowSize()
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return Vector2(w, h);
}

void Renderer::LimitFramerate(int fps)
{
    SDL_Delay((Uint32)(1000 / fps));
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void Renderer::Render()
{
    SDL_RenderPresent(renderer);
}

void Renderer::DrawPointF(Vector2 position, float pt, Color color)
{
    DrawPointF(position.x, position.y, pt, color);
}

void Renderer::DrawPointF(float x, float y, float pt, Color color)
{
    SetRenderDrawColor(color);
    SetRenderScale(pt);
    SDL_RenderDrawPointF(renderer, x / pt, y / pt);
    SetRenderScale(1);
}

void Renderer::DrawLineF(Line line, float pt, Color color)
{
    DrawLineF(line.start.x, line.start.y, line.end.x, line.end.y, pt, color);
}

void Renderer::DrawLineF(float x1, float y1, float x2, float y2, float pt, Color color)
{
    SetRenderDrawColor(color);
    SetRenderScale(pt);
    SDL_RenderDrawLineF(renderer, x1 / pt, y1 / pt, x2 / pt, y2 / pt);
    SetRenderScale(1);
}