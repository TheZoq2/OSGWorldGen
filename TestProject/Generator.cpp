#include "Generator.h"

float Generator::rand1d(float x, float seed)
{
	float randVal = sin(x*1252.25126) * seed;
	return randVal - floor(randVal);
}
float Generator::rand2d(float x, float y, float seed)
{
	float randVal = sin(x*12.9898 + y*78.233) * seed;
	return randVal - floor(randVal); //Making 0 < randVal < 1
}

/*float Generator::getPointHeight(float x, float z, float detailLevel)
{
	//float points[4];//The 4 reference points

	//Calculating what point to get the height from
	float xPoint = floor(x / detailLevel);
	float zPoint = floor(z / detailLevel);

	//Calculating heights
	float xValue1 = cos((x - xPoint) / detailLevel * M_PI);
	float xValue2 = 1 - xValue1;
	float zValue1 = cos((z - zPoint) / detailLevel * M_PI);
	float zValue2 = 1 - zValue1;

	float finalXValue1 = xValue1 * zValue1;
	float finalXValue2 = xValue2 * zValue2;

	float height = Generator::rand2d(xPoint, zPoint, 21236) * finalXValue1 + Generator::rand2d(xPoint + detailLevel, zPoint, 21236) * finalXValue2;

	return height;
}*/

float Generator::getPointHeight(float x, float z, float detailLevel)
{
	float seed = 61236.24;

	float height = 0;

	//Calculating the height of all the points
	float xPoint1 = floor(x / detailLevel) * detailLevel;
	float xPoint2 = xPoint1 + detailLevel;

	float zPoint1 = floor(z / detailLevel) * detailLevel;
	float zPoint2 = zPoint1 + detailLevel;

	//Calculating which curves have the most influence
	float xDist = x - xPoint1;
	float zDist = z - zPoint1;

	float xInf1 = xDist / detailLevel;
	float xInf2 = 1 - xInf1;

	float zInf1 = zDist / detailLevel;
	float zInf2 = 1 - zInf1;

	//Calculating the final height of the point

	//calculating the heights
	float heightx1z1 = rand2d(xPoint1, zPoint1, seed);
	float heightx1z2 = rand2d(xPoint1, zPoint2, seed);
	float heightx2z1 = rand2d(xPoint2, zPoint1, seed);
	float heightx2z2 = rand2d(xPoint2, zPoint2, seed);

	//Calculating the curves
	//Interpolate between x1;z1 and x1;z2 based on the distance between x and the final x point
	float xCurve1 = interpolateCos(heightx1z1, heightx2z1, (x - xPoint1) / detailLevel);
	float xCurve2 = interpolateCos(heightx1z2, heightx2z2, (x - xPoint1) / detailLevel);

	float zCurve1 = interpolateCos(heightx1z1, heightx1z2, (z - zPoint1) / detailLevel);
	float zCurve2 = interpolateCos(heightx2z1, heightx2z2, (z - zPoint1) / detailLevel);

	float finalX = xCurve1 * zInf2 + xCurve2 * zInf1;
	float finalZ = zCurve1 * xInf2 + zCurve2 * xInf1;

	//height = xCurve1 *zInf2 + xCurve2 * zInf1;

	height = 0.5 * finalX + 0.5*finalZ;
	//height = finalZ;

	return height;
}

float Generator::interpolateCos(float x1, float x2, float dist)
{
	float result = 0;

	float cosVal = 0.5 + (cos(dist * M_PI) * 0.5);

	float val1 = (x1 * cosVal);
	float val2 = (x2 * (1-cosVal));

	result =  val1 + val2;

	//result = x2 * dist + x1 * (1 - dist);

	return result;
}
