#pragma once

#include "Voxel.h"
#include <list>
#include <cmath>

class Chunk {
private:
    std::list<Voxel> voxels_;

public:
    Chunk(int size);

    const std::list<Voxel> voxels();
};