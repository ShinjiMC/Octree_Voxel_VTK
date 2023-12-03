#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Reader/Reader.hpp"
#include "../Vtk_Builder/vtk_builder.hpp"

// Función para leer los puntos desde el archivo CSV y realizar pruebas EXPECT_TRUE
void testPointsOctree(const std::string &filename, Octree &octree)
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

void testLoadRenderInteractClear(Vtk_Builder &vtkBuilder, const Octree &octree, int option)
{
    ASSERT_NO_THROW({
        vtkBuilder.loadOctree(octree, option);
        vtkBuilder.render();
        vtkBuilder.startInteractor();
        vtkBuilder.clear();
    });
}

TEST(OctreeTest, PointsFromCSVTest_1)
{
    Octree octree;
    Reader csv;
    Vtk_Builder vtkBuilder;
    octree = csv.readAndConvert(1);
    std::string filename = "../Resources/points1.csv";
    testPointsOctree(filename, octree);
    testLoadRenderInteractClear(vtkBuilder, octree, 1);
    testLoadRenderInteractClear(vtkBuilder, octree, 2);
    testLoadRenderInteractClear(vtkBuilder, octree, 3);
}

TEST(OctreeTest, PointsFromCSVTest_2)
{
    Octree octree;
    Reader csv;
    Vtk_Builder vtkBuilder;
    octree = csv.readAndConvert(2);
    std::string filename = "../Resources/points2.csv";
    testPointsOctree(filename, octree);
    testLoadRenderInteractClear(vtkBuilder, octree, 1);
    testLoadRenderInteractClear(vtkBuilder, octree, 2);
    testLoadRenderInteractClear(vtkBuilder, octree, 3);
}

TEST(OctreeTest, PointsFromCSVTest_3)
{
    Octree octree;
    Reader csv;
    Vtk_Builder vtkBuilder;
    octree = csv.readAndConvert(3);
    std::string filename = "../Resources/points3.csv";
    testPointsOctree(filename, octree);
}

TEST(OctreeTest, PointsFromCSVTest_4)
{
    Octree octree;
    Reader csv;
    Vtk_Builder vtkBuilder;
    octree = csv.readAndConvert(4);
    std::string filename = "../Resources/points4.csv";
    testPointsOctree(filename, octree);
}

TEST(OctreeTest, PointsFromCSVTest_5)
{
    Octree octree;
    Reader csv;
    Vtk_Builder vtkBuilder;
    octree = csv.readAndConvert(5);
    std::string filename = "../Resources/points5.csv";
    testPointsOctree(filename, octree);
}

TEST(OctreeTest, PointsFromCSVTest_6)
{
    Octree octree;
    Reader csv;
    Vtk_Builder vtkBuilder;
    octree = csv.readAndConvert(6);
    std::string filename = "../Resources/points6.csv";
    testPointsOctree(filename, octree);
}