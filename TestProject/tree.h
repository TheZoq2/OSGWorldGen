#ifndef TREE_H
#define TREE_H

#include<vector>
#include<string>

#include "object.h"

#include<osg/PositionAttitudeTransform>
#include<osg/Quat>
#include<osg/Texture2D>
#include<osg/Image>
#include<osg/BlendFunc>
#include<osgDB/ReadFile>

#include"branch.h"
#include"lodobject.h"

namespace TreeGen
{
	float tallFirBranchLength(float y); ///Get the lenght of a branch in a fir tree at height y. Where y is the height at y / height
}

class Tree: public LODObject
{
public:
	Tree();

	void generateFir(float height, int segments, float seed, unsigned int branchAmount, float branchStart);
	void setLeafTexture(std::string filename);

	//osg::PositionAttitudeTransform* getRoot();
private:
	void addBranch(osg::Vec3 position, osg::Quat rotation, float length, float segments, float minAngleX, float maxAngleX, float minAngleZ, float maxAngleZ, float seed);

	osg::Texture2D* leafTexture;
	osg::Image* leafImage;
	osg::StateSet* leafStateSet;

	float heignt;
	int segments;

	float seed;

	Branch trunk;
	std::vector< Branch > branches;

	osg::Group* highLod;
};

#endif // TREE_H
