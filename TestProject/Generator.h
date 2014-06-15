#ifndef GENERATOR_H
#define GENERATOR_H

#include "math.h"


namespace Generator
{
	float rand1d(float x, float seed);
	float rand2d(float x, float y, float seed);

	float getPointHeight(float x, float z, float detailLevel, float seed);
	float getTerrainHeight(float x, float y, float seed);

	float interpolateCos(float x1, float x2, float dist);
}
#endif // GENERATOR_H
