#include "dataImporter.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

std::vector<Vector2> DataImporter::ImportPoints(std::string path)
{
    std::cout << path << std::endl;

    std::string line;
    std::ifstream file;
    file.open(path);

    if (!file.is_open()) 
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    std::getline(file, line);
    size_t lines = std::stoi(line);

    std::vector<Vector2> points;

    for (size_t i = 0; i < lines; i++)
    {
        std::getline(file, line);
        std::istringstream iss(line);
        int x, y;
        if (!(iss >> x >> y)) { break; }

        points.push_back(Vector2(x, y));
    }

    return points;
}