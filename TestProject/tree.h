#ifndef TREE_H
#define TREE_H

#include <vector>

#include "object.h"

#include<osg/PositionAttitudeTransform>
#include<osg/Quat>

#include"branch.h"

class Tree: public Object
{
public:
	Tree();

	void generateFir(float height, int segments, float seed);

	//osg::PositionAttitudeTransform* getRoot();
private:
	void addBranch(osg::Vec3 position, osg::Quat rotation, float length, float segments, float minAngleX, float maxAngleX, float minAngleZ, float maxAngleZ, float seed);

	osg::Vec3Array* vertecies;

	float heignt;
	int segments;

	float seed;

	Branch trunk;
	std::vector< Branch > branches;
};

#endif // TREE_H
