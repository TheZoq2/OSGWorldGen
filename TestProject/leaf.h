#ifndef LEAF_H
#define LEAF_H

#include "object.h"

#include<osg/Billboard>
#include<osg/Geometry>

class Leaf : public Object
{
public:
	Leaf();

	void create(float width, float height, float centerX, float centerZ);
private:
	osg::Billboard* billboard;
	osg::Geometry* geometry;
	osg::Vec3Array* vertecies;

	float width;
	float height;

	float centerX;
	float centerZ;
};

#endif // LEAF_H
