#include "tree.h"

float TreeGen::tallFirBranchLength(float y)
{
	float value = -pow(9.0/6.0*y-0.5, 2) + 1;
	return value;
}

Tree::Tree()
{
	setupLod(2);
}

void Tree::generateFir(float height, int segments, float seed, unsigned int branchAmount, float branchStart)
{
	//root = new osg::PositionAttitudeTransform;
	highLod = new osg::Group;

	//Setting parameters
	//float height = 15;
	float startingRadius = height / 45;
	float endRadius = 0.05f;
	//int segments = 10;
	this->seed = seed;

	trunk.generate(height, segments, startingRadius, endRadius, 0, 10, -0.2, 0.2, -0.2, 0.2, seed);

	highLod->addChild(trunk.getRoot());

	//root->addChild(trunk.getRoot());
	//this->addObject();

	//Adding branches
	//float branchStart = height / 7;
	branchStart = branchStart * height;

	float branchY = branchStart + Generator::rand1d(10, seed) * (height - branchStart); //Calculating the position of the first branch

	for(unsigned int i = 0; i < branchAmount; i++)
	{
		//Selecting a position for the branch
		branchY = branchStart + Generator::rand1d(branchY, seed) * (height - (height / 6) - branchStart);

		osg::Vec3 branchPos = trunk.getCenter(branchY);

		//Calculating the length of the branch
		//float branchLenth = (1 - branchY / height) * (height / 1.7777);
		float branchLength = TreeGen::tallFirBranchLength(branchY / height) * height * 0.25;

		int branchSegments = 6;

		//Calculating the target angle of the branch
		float angleY = M_PI * 2 * Generator::rand1d(branchY, seed);

		float targetX = cos(angleY);
		float targetY = -0.3;
		float targetZ = sin(angleY);
		//calculating the rotation of the branch
		osg::Quat rotation;
		rotation.makeRotate(osg::Vec3(0, 1, 0), osg::Vec3(targetX, targetY, targetZ));

		//osg::Vec3 position = osg::Vec3(0, branchY, 0);

		addBranch(branchPos, rotation, branchLength, branchSegments, -0.2, 0.2, -0.2, 0.2, seed);
	}

	//Adding the leaves to the root object
	for(unsigned int i = 0; i < branches.size(); i++)
	{
		Branch* branch = &branches.at(i);
		branch->addLeaves(5, 2, 2, 1, 1, 0.3, 1);
	}

	trunk.addLeaves(5, 2, 2, 1, 1, 0.8, 1);

	this->addLodObject(highLod, 0);
}


void Tree::addBranch(osg::Vec3 position, osg::Quat rotation, float length, float segments, float minAngleX, float maxAngleX, float minAngleZ, float maxAngleZ, float seed)
{
	//Calculating the parameters for the branch
	float startRadius = length / 50;
	float endRadius = 0.01f;
	float ringAmount = 5;

	Branch branch;
	branch.generate(length, segments, startRadius, endRadius, 0, ringAmount, minAngleX, maxAngleX, minAngleZ, maxAngleZ, seed);

	branch.setPosition(position);
	branch.setRotation(rotation);

	highLod->addChild(branch.getRoot());

	branches.push_back(branch);
}
void Tree::setLeafTexture(std::string filename)
{
	leafImage = new osg::Image;
	leafTexture = new osg::Texture2D;

	leafTexture->setDataVariance(osg::Object::DYNAMIC);

	leafImage = osgDB::readImageFile(filename);
	if(!leafImage)
	{
		std::cout << "Failed to load leaf texture, File: " << filename << " did not exist" << std::endl;
		return;
	}

	leafTexture->setImage(leafImage);

	//Setting up the stateset
	leafStateSet = new osg::StateSet;

	leafStateSet->setTextureAttributeAndModes(0, leafTexture, osg::StateAttribute::ON);
	leafStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	leafStateSet->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), osg::StateAttribute::ON);

	//Assiging the stateset to all the leaves
	for(unsigned int i = 0; i < branches.size(); i++)
	{
		Branch* branch = &branches.at(i);
		branch->setLeafStateSet(leafStateSet);
	}
	trunk.setLeafStateSet(leafStateSet);
}
