#include "Chunk.h"

#define DB_PERLIN_IMPL
#include "db_perlin.hpp"

Chunk::Chunk(int size) : voxels_() {
    int cubeRoot = cbrt(size);

	GLfloat frequency = 0.05f;
	for (int x = 0; x < cubeRoot; x++) {
		for (int y = 0; y < cubeRoot; y++) {
			for (int z = 0; z < cubeRoot; z++) {
				Voxel v;
				GLfloat noise = db::perlin(x * frequency, y * frequency, z * frequency);
				std::cout << noise << std::endl;
				if (noise < 0.05 && noise > 0.01) noise = -1;
				else if (noise > 0.05) noise = 1;
				else noise = 0;
				
				v.translate(x + noise, y + noise, z + noise);
				voxels_.push_back(v);
			}
		}
	}
}

const std::list<Voxel> Chunk::voxels() {
    return voxels_;
}