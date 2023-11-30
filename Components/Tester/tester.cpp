#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Reader/Reader.hpp"

// Función para leer los puntos desde el archivo CSV y realizar pruebas EXPECT_TRUE
void testPointsInOctree(const std::string &filename, Octree &octree)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string token;
        double x, y, z;

        if (std::getline(ss, token, ','))
            x = std::stod(token);
        if (std::getline(ss, token, ','))
            y = std::stod(token);
        if (std::getline(ss, token, '\n'))
            z = std::stod(token);

        EXPECT_TRUE(octree.find(Vec3D(x, y, z))) << "Point (" << x << ", " << y << ", " << z << ") not found in the Octree.";
    }
    file.close();
}

TEST(OctreeTest, PointsFromCSVTest_1)
{
    Octree octree;
    Reader csv;
    octree = csv.readAndConvert(1);
    std::string filename = "../Resources/points1.csv";
    testPointsInOctree(filename, octree);
}

TEST(OctreeTest, PointsFromCSVTest_2)
{
    Octree octree;
    Reader csv;
    octree = csv.readAndConvert(2);
    std::string filename = "../Resources/points2.csv";
    testPointsInOctree(filename, octree);
}

TEST(OctreeTest, PointsFromCSVTest_3)
{
    Octree octree;
    Reader csv;
    octree = csv.readAndConvert(3);
    std::string filename = "../Resources/points3.csv";
    testPointsInOctree(filename, octree);
}