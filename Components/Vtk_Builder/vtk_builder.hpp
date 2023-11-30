#ifndef VTK_BUILDER_HPP
#define VTK_BUILDER_HPP

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
    void loadOctree(const Octree &octree);
    void addCubeActor(vtkSmartPointer<vtkActor> cubeActor);
    void render();
    void startInteractor();

private:
    void loading(Octant *octant);
    vtkSmartPointer<vtkActor> createCube(double x, double y, double z, double sideLength);
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
};

#endif // VTK_BUILDER_HPP