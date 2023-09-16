#pragma once

struct Vector2
{
    float x;
    float y;

    Vector2()
    {
        this->x = 0;
        this->y = 0;
    }

    Vector2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

struct Line
{
    Vector2 start;
    Vector2 end;

    Line()
    {
        this->start = Vector2();
        this->end = Vector2();
    }
    
    Line(Vector2 start, Vector2 end)
    {
        this->start = start;
        this->end = end;
    }
};
