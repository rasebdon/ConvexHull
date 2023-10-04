#include "dataImporter.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

std::vector<Vector2> DataImporter::ImportPoints(std::string path)
{
    std::cout << "Importing points:" << path << std::endl;

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
        
        int delimiterIndex = line.find(',');
        float x = std::stof(line.substr(0, delimiterIndex));
        float y = std::stof(line.substr(delimiterIndex + 1, (line.size() - delimiterIndex)));

        points.push_back(Vector2(x, y));
    }
    file.close();

    std::cout << "Imported " << points.size() << " points" << std::endl;

    return points;
}