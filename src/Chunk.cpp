#include "Chunk.h"
#include "util/noise.h"

Chunk::Chunk(int size) : voxels_() {
    int cubeRoot = cbrt(size);

	GLfloat frequency = 0.05f;
	for (int x = 0; x < cubeRoot; x++) {
		for (int y = 0; y < cubeRoot; y++) {
			for (int z = 0; z < cubeRoot; z++) {
				Voxel v;
				GLfloat noise = noise::calculate3d(x, y, z, frequency);
				if (noise < 0.1) noise = -1;
				else if (noise > 0.15) noise = 1;
				else noise = 0;

				v.translate(x, noise, z);
				voxels_.push_back(v);
			}
		}
	}
	noise::reseed();
}

Chunk::Chunk(int size, glm::vec3 offset) : voxels_() {
    int cubeRoot = cbrt(size);

	GLfloat frequency = 0.05f;
	for (int x = 0; x < cubeRoot; x++) {
		for (int y = 0; y < cubeRoot; y++) {
			for (int z = 0; z < cubeRoot; z++) {
				Voxel v;
				GLfloat noise = noise::calculate3d(x, y, z, frequency);
				if (noise < 0.01) noise = -1;
				else if (noise > 0.15) noise = 1;
				else noise = 0;

				v.translate(x + offset.x, noise + offset.y, z + offset.z);
				voxels_.push_back(v);
			}
		}
	}
	noise::reseed();
}

const std::list<Voxel> Chunk::voxels() {
    return voxels_;
}