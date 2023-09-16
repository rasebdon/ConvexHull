#pragma once
#include <vector>
#include <string>
#include "geometry.h"

class DataImporter
{
public:
    static std::vector<Vector2> ImportPoints(std::string path);
};