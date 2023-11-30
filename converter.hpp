#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include "octree.hpp"
#include "octree.cpp"

class Converter
{
public:
    std::vector<Vec3D> readAndConvert(int fileNumber);
};

std::vector<Vec3D> Converter::readAndConvert(int fileNumber)
{
    std::string filename = "points" + std::to_string(fileNumber) + ".csv";
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return std::vector<Vec3D>(0);
    }
    std::vector<Vec3D> points;
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string token;
        double x, y, z;
        if (std::getline(ss, token, ','))
            x = std::stoi(token);
        if (std::getline(ss, token, ','))
            y = std::stoi(token);
        if (std::getline(ss, token, '\n'))
            z = std::stoi(token);
        points.push_back(Vec3D(x, y, z));
    }
    file.close();
    return points;
}

#endif // CONVERTER_HPP