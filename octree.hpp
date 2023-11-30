#ifndef OCTREE_HPP
#define OCTREE_HPP

#include "vec3d.hpp"

class Octree
{
private:
    Vec3D point; // Puede ser el medio del octante o el punto almacenado
    double h;
    bool isLeaf;
    Octree *octantes[8];

public:
    Octree();
    ~Octree();
    void insert(const Vec3D &pos);

private:
    void insert(Octree octant, Vec3D pos);
    int getIndex(const Vec3D &pos) const;
};
#endif // OCTREE_HPP