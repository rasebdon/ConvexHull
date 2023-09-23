#pragma once
#include <SDL.h>
#include "geometry.h"
#include "color.h"

class Renderer
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;

    Color GetRenderDrawColor() const;
    void SetRenderDrawColor(const Color& color) const;
    void SetRenderScale(const float& scale) const;
public:
    Renderer(size_t width, size_t height);
    ~Renderer();

    Vector2 getWindowSize() const;
    void LimitFramerate(int fps) const;

    /// @brief Called to clear the current rendered window
    void Clear() const;
    void Render() const;

    /// @brief Draw a point at the specified location with the pt thickness
    /// @param position Position of the point
    /// @param pt Point size
    /// @param color Color of the point
    void DrawPointF(Vector2 position, float pt, Color color) const;

    /// @brief Draw a point at the specified location with the pt thickness
    /// @param x X Position of the point
    /// @param y Y Position of the point
    /// @param pt Point size
    /// @param color Color of the point
    void DrawPointF(float x, float y, float pt, Color color) const;

    /// @brief Draw a line from start to end with the pt thickness
    /// @param line Line object to draw
    /// @param pt Line thickness
    /// @param color Color of the line
    void DrawLineF(Line line, float pt, Color color) const;

    /// @brief Draw a line from start to end with the pt thickness
    /// @param x1 Line start x
    /// @param y1 Line start y
    /// @param x2 Line end x
    /// @param y2 Line end y
    /// @param pt Line thickness
    /// @param color Color of the line
    void DrawLineF(float x1, float y1, float x2, float y2, float pt, Color color) const;
};
