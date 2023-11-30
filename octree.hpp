#ifndef OCTREE_HPP
#define OCTREE_HPP

#include "vec3d.hpp"

struct Octant
{
    Vec3D point, midCube; // Puede ser el medio del octante o el punto almacenado
    double h;
    bool isLeaf;
    Octant *octantes[8];
};

class Octree
{
private:
    Octant *root;

public:
    Octree() : root(nullptr){};
    ~Octree() = default;
    void insert(const Vec3D &pos);
    bool find(const Vec3D &pos) const;
    void print();

private:
    void insertion(Octant *&octant, Vec3D pos, double h, Vec3D NewmidCube);
    int getIndex(const Vec3D &pos, const Vec3D &mid) const;
    Vec3D calculateOctantMidpoint(const Vec3D &midCube, double cubeSize, int octantIndex);
    void printOctant(Octant *octant, int level);
};
#endif // OCTREE_HPP