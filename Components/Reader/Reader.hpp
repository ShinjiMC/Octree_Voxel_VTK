#ifndef READER_HPP
#define READER_HPP

#include "../Octree/octree.hpp"
class Reader
{
public:
    Octree readAndConvert(int fileNumber);
};

#endif // READER_HPP