#include "octree.hpp"

int Octree::getIndex(const Vec3D &pos) const
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
    if (pos.getX() < this->point.getX())
        index += 4;
    if (pos.getY() < this->point.getY())
        index += 2;
    if (pos.getZ() < this->point.getZ())
        index += 1;

    return index;
}

void Octree::insert(const Vec3D &pos)
{
}