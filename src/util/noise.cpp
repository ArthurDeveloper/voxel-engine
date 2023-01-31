#include "noise.h"

siv::PerlinNoise::seed_type seed = 123456u;
siv::PerlinNoise perlin { seed };

const double noise::calculate3d(double x, double y, double z, double frequency) {
	const double noise = perlin.noise3D(x * frequency, y * frequency, z * frequency);
	return noise;
}

void noise::reseed() {
	seed = rand() % 100000;
	perlin.reseed(seed);
}