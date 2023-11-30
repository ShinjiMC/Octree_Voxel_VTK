#ifndef VTK_BUILDER_HPP
#define VTK_BUILDER_HPP

#include <vtkProperty.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include "../Octree/octree.hpp"

class Vtk_Builder
{
public:
    Vtk_Builder();
    ~Vtk_Builder() = default;
    void loadOctree(const Octree &octree, const int &opt);
    void addCubeActor(vtkSmartPointer<vtkActor> cubeActor);
    void render();
    void startInteractor();
    void clear();

private:
    void loading1(Octant *octant);
    void loading2(Octant *octant);
    void loading3(Octant *octant);
    vtkSmartPointer<vtkActor> createCube(double x, double y, double z, double sideLength);
    vtkSmartPointer<vtkActor> createPoint(double x, double y, double z);
    vtkSmartPointer<vtkActor> createCubeT(double x, double y, double z, double sideLength);
    vtkSmartPointer<vtkActor> createPointT(double x, double y, double z, double sideLength);
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
};

#endif // VTK_BUILDER_HPP