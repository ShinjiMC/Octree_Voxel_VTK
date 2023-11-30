#include <iostream>
#include <fstream>
#include <sstream>
#include "Reader.hpp"

Octree Reader::readAndConvert(int fileNumber)
{
    std::string filename = "../Resources/points" + std::to_string(fileNumber) + ".csv";
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return Octree();
    }
    Octree octree;
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
        octree.insert(Vec3D(x, y, z));
    }
    file.close();
    return octree;
}