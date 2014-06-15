#ifndef LEAF_H
#define LEAF_H

#include "object.h"

#include<osg/Billboard>
#include<osg/Geometry>

extern int leafAmount;

class Leaf : public Object
{
public:
	Leaf();

	void create(float width, float height, float centerX, float centerZ);

	void setStateSet(osg::StateSet* stateSet);
private:
	osg::Billboard* billboard;
	osg::Geometry* geometry;
	osg::Vec3Array* vertecies;
	osg::Vec2Array* textureCoords;

	float width;
	float height;

	float centerX;
	float centerZ;
};

#endif // LEAF_H
