#include "vtk_builder.hpp"

Vtk_Builder::Vtk_Builder()
{
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
}

vtkSmartPointer<vtkActor> Vtk_Builder::createCube(double x, double y, double z, double sideLength)
{
    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    cubeSource->SetCenter(x, y, z);
    cubeSource->SetXLength(sideLength);
    cubeSource->SetYLength(sideLength);
    cubeSource->SetZLength(sideLength);
    cubeSource->Update();

    vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

    vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
    cubeActor->SetMapper(cubeMapper);

    return cubeActor;
}

void Vtk_Builder::addCubeActor(vtkSmartPointer<vtkActor> cubeActor)
{
    renderer->AddActor(cubeActor);
}

void Vtk_Builder::render()
{
    renderWindow->Render();
}

void Vtk_Builder::startInteractor()
{
    renderWindowInteractor->Start();
}

void Vtk_Builder::loadOctree(const Octree &octree)
{
    loading(octree.getroot());
}

void Vtk_Builder::loading(Octant *octant)
{
    if (octant == nullptr)
        return;

    if (octant->isLeaf)
    {
        double x = octant->midCube.getX();
        double y = octant->midCube.getY();
        double z = octant->midCube.getZ();
        double sideLength = octant->h;
        vtkSmartPointer<vtkActor> cubeActor = createCube(x, y, z, sideLength);
        addCubeActor(cubeActor);
    }
    for (int i = 0; i < 8; i++)
        loading(octant->octantes[i]);
}