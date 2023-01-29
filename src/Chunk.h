#pragma once

#include "Voxel.h"
#include "glm/ext/vector_float3.hpp"
#include <list>
#include <cmath>

class Chunk {
private:
    std::list<Voxel> voxels_;

public:
    Chunk(int size);
    Chunk(int size, glm::vec3 offset);

    const std::list<Voxel> voxels();
};