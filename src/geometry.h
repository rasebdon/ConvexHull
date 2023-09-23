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

    bool operator==(const Vector2& other)
    {
        return other.x == x && other.y == y;
    }

    static int crossProduct(const Vector2& A, const Vector2& B, const Vector2& C)
    {
        return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
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