#pragma once
#include <string>

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

    bool operator==(const Vector2& other) const
    {
        return other.x == x && other.y == y;
    }

    static float crossProduct(const Vector2& A, const Vector2& B, const Vector2& C)
    {
        return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    }

    std::string toString() const
    {
        return std::string("(").append(std::to_string(x)).append(", ").append(std::to_string(y)).append(")");
    }

    static bool arePointsColinear(const Vector2& A, const Vector2& B, const Vector2& C, float epsilon = 1e-5)
    {
        int crossProduct = Vector2::crossProduct(A, B, C);
        return std::abs(crossProduct) < epsilon;
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