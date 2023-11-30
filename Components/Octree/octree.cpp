#include "octree.hpp"
#include <iostream>
int Octree::getIndex(const Vec3D &pos, const Vec3D &mid) const
{
    // Indices are made such that we have
    //   x y z
    // 0 + + +
    // 1 + + -
    // 2 + - +
    // 3 + - -
    // 4 - + +
    // 5 - + -
    // 6 - - +
    // 7 - - -

    int index = 0;
    if (pos.getX() < mid.getX())
        index += 4;
    if (pos.getY() < mid.getY())
        index += 2;
    if (pos.getZ() < mid.getZ())
        index += 1;
    return index;
}

Vec3D Octree::calculateOctantMidpoint(const Vec3D &midCube, double cubeSize, int octantIndex)
{
    double offset = cubeSize / 4.0;                        // El cubo se divide en 8 octantes, cada uno tiene un cuarto del tamaño
    double offsetX = (octantIndex & 4) ? -offset : offset; // Bit 2 representa el eje X
    double offsetY = (octantIndex & 2) ? -offset : offset; // Bit 1 representa el eje Y
    double offsetZ = (octantIndex & 1) ? -offset : offset; // Bit 0 representa el eje Z

    // Calculamos el punto medio del octante relativo al cubo grande
    double midX = midCube.getX() + offsetX;
    double midY = midCube.getY() + offsetY;
    double midZ = midCube.getZ() + offsetZ;
    return Vec3D(midX, midY, midZ);
}

void Octree::insert(const Vec3D &pos)
{
    if (this->find(pos))
    {
        // std::cout << "El punto ya existe en el Octree." << std::endl;
        return;
    }

    if (this->root == nullptr)
    {
        // std::cout << "Insertando el primer punto en el Octree." << std::endl;
        this->root = new Octant();
        this->root->midCube = Vec3D();
        this->root->point = this->root->midCube;
        this->root->h = 2000;
        this->root->isLeaf = false;
        for (int i = 0; i < 8; i++)
            this->root->octantes[i] = nullptr;
    }

    int index = this->getIndex(pos, this->root->midCube);
    // std::cout << "Índice calculado: " << index << std::endl;

    Vec3D calculatedMidCube = calculateOctantMidpoint(this->root->midCube, this->root->h, index);
    // std::cout << "Punto medio calculado: (" << calculatedMidCube.getX() << ", " << calculatedMidCube.getY() << ", " << calculatedMidCube.getZ() << ")" << std::endl;

    this->insertion(this->root->octantes[index], pos, this->root->h / 2, calculatedMidCube);
}

void Octree::insertion(Octant *&octant, Vec3D pos, double h, Vec3D NewmidCube)
{
    if (octant == nullptr)
    {
        // std::cout << "Creando un nuevo punto." << std::endl;
        octant = new Octant();
        octant->point = pos;
        octant->midCube = NewmidCube;
        octant->h = h;
        octant->isLeaf = true;
        for (int i = 0; i < 8; i++)
            octant->octantes[i] = nullptr;
    }
    else
    {
        if (octant->isLeaf)
        {
            // std::cout << "Creando un nuevo octante a partir de un punto." << std::endl;
            double h = octant->h;
            Vec3D point = octant->point;
            octant->point = octant->midCube;
            octant->isLeaf = false;
            int index = getIndex(point, octant->midCube);
            // std::cout << "Índice calculado de point ya existente: " << index << std::endl;
            Vec3D Newmid = calculateOctantMidpoint(octant->midCube, octant->h, index);
            // std::cout << "Punto medio calculado: (" << Newmid.getX() << ", " << Newmid.getY() << ", " << Newmid.getZ() << ")" << std::endl;
            this->insertion(octant->octantes[index], point, h / 2, Newmid);
            // std::cout << "Insertoooooo1" << std::endl;

            index = getIndex(pos, octant->midCube);
            // std::cout << "Índice calculado de point nuevo: " << index << std::endl;
            Newmid = calculateOctantMidpoint(octant->midCube, octant->h, index);
            // std::cout << "Punto medio calculado: (" << Newmid.getX() << ", " << Newmid.getY() << ", " << Newmid.getZ() << ")" << std::endl;
            this->insertion(octant->octantes[index], pos, h / 2, Newmid);
            // std::cout << "Insertoooooo2" << std::endl;
        }
        else
        {
            // std::cout << "Ingresando a un octante mas profundo." << std::endl;
            int index = getIndex(pos, octant->midCube);
            Vec3D NewmidCube = calculateOctantMidpoint(octant->midCube, octant->h, index);
            this->insertion(octant->octantes[index], pos, octant->h / 2, NewmidCube);
            // std::cout << "Insertoooooo3" << std::endl;
        }
    }
}

bool Octree::find(const Vec3D &pos) const
{
    if (this->root == nullptr)
        return false;
    int index = this->getIndex(pos, this->root->midCube);
    Octant *octant = this->root->octantes[index];
    while (octant != nullptr)
    {
        if (octant->isLeaf)
        {
            if (octant->point == pos)
                return true;
            else
                return false;
        }
        else
        {
            index = this->getIndex(pos, octant->midCube);
            octant = octant->octantes[index];
        }
    }
    return false;
}

void Octree::print()
{
    printOctant(this->root, 0);
}

void Octree::printOctant(Octant *octant, int level)
{
    if (octant == nullptr)
        return;

    if (octant->isLeaf)
    {
        std::cout << "Level " << level << ": " << octant->point.getX() << " " << octant->point.getY() << " " << octant->point.getZ() << " - H: " << octant->h;
        std::cout << " - MID: " << octant->midCube.getX() << " " << octant->midCube.getY() << " " << octant->midCube.getZ() << std::endl;
        return;
    }

    for (int i = 0; i < 8; ++i)
    {
        printOctant(octant->octantes[i], level + 1);
    }
}

Octant *Octree::getroot() const
{
    return this->root;
}