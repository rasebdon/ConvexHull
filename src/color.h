#pragma once

struct Color
{
    int r;
    int g;
    int b;
    int a;

    Color(int r, int g, int b, int a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    };

    Color(int r, int g, int b) : Color(r, g, b, 255) {}
    Color() : Color(0, 0, 0) {}

    static Color Black() { return Color(0, 0, 0, 255); };
    static Color Red() { return Color(255, 0, 0, 255); };
};