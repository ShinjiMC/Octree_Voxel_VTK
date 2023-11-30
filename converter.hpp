#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "vec3d.hpp"
#include "octree.hpp"
class Converter
{
public:
    Octree readAndConvert(int fileNumber);
};

Octree Converter::readAndConvert(int fileNumber)
{
    std::string filename = "points" + std::to_string(fileNumber) + ".csv";
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return Octree();
    }
    Octree octree;
    std::string line;
    int c = 1;
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
        octree.insert(Vec3D(x, y, z));
        // std::cout << "Line: " << c++ << std::endl;
    }
    file.close();
    return octree;
}

#endif // CONVERTER_HPP