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

    vtkSmartPointer<vtkProperty> cubeProperty = vtkSmartPointer<vtkProperty>::New();
    cubeProperty->SetColor(0.0, 1.0, 0.0); // Verde
    cubeActor->SetProperty(cubeProperty);

    return cubeActor;
}

vtkSmartPointer<vtkActor> Vtk_Builder::createPoint(double x, double y, double z)
{
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(x, y, z);
    sphereSource->SetRadius(1.0);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkProperty> pointProperty = vtkSmartPointer<vtkProperty>::New();
    pointProperty->SetColor(1.0, 0.0, 0.0); // Rojo
    actor->SetProperty(pointProperty);

    return actor;
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

void Vtk_Builder::loadOctree(const Octree &octree, const int &opt)
{
    if (opt == 1)
        loading1(octree.getroot());
    else if (opt == 2)
        loading2(octree.getroot());
    else if (opt == 3)
        loading3(octree.getroot());
}

void Vtk_Builder::loading1(Octant *octant)
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
        loading1(octant->octantes[i]);
}

void Vtk_Builder::loading2(Octant *octant)
{
    if (octant == nullptr)
        return;

    if (octant->isLeaf)
    {
        double x = octant->point.getX();
        double y = octant->point.getY();
        double z = octant->point.getZ();
        vtkSmartPointer<vtkActor> pointActor = createPoint(x, y, z);
        addCubeActor(pointActor);
    }
    for (int i = 0; i < 8; i++)
        loading2(octant->octantes[i]);
}

void Vtk_Builder::loading3(Octant *octant)
{
    if (octant == nullptr)
        return;

    if (octant->isLeaf)
    {
        double sideLength = octant->h;
        double x = octant->point.getX();
        double y = octant->point.getY();
        double z = octant->point.getZ();
        vtkSmartPointer<vtkActor> pointActor = createPointT(x, y, z, sideLength);
        addCubeActor(pointActor);

        double x2 = octant->midCube.getX();
        double y2 = octant->midCube.getY();
        double z2 = octant->midCube.getZ();
        vtkSmartPointer<vtkActor> cubeActor = createCubeT(x2, y2, z2, sideLength);
        addCubeActor(cubeActor);
    }
    for (int i = 0; i < 8; i++)
        loading3(octant->octantes[i]);
}

vtkSmartPointer<vtkActor> Vtk_Builder::createCubeT(double x, double y, double z, double sideLength)
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

    vtkSmartPointer<vtkProperty> cubeProperty = vtkSmartPointer<vtkProperty>::New();
    cubeProperty->SetColor(0.0, 1.0, 0.0); // Verde

    // Configurar para mostrar solo los bordes y hacer el interior transparente
    cubeProperty->SetEdgeVisibility(1);
    cubeProperty->SetOpacity(0.2);

    cubeActor->SetProperty(cubeProperty);

    return cubeActor;
}

vtkSmartPointer<vtkActor> Vtk_Builder::createPointT(double x, double y, double z, double sideLength)
{
    double pointRadius = sideLength * 0.05;
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(x, y, z);
    sphereSource->SetRadius(pointRadius);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkProperty> pointProperty = vtkSmartPointer<vtkProperty>::New();
    pointProperty->SetColor(1.0, 0.0, 0.0); // Rojo
    actor->SetProperty(pointProperty);

    return actor;
}

void Vtk_Builder::clear()
{
    renderer->RemoveAllViewProps();
}