#include "tree.h"

Tree::Tree()
{
}

void Tree::generateFir(float height, int segments, float seed)
{
	root = new osg::PositionAttitudeTransform;

	//Setting parameters
	//float height = 15;
	float startingRadius = height / 30;
	float endRadius = 0.05f;
	//int segments = 10;
	this->seed = seed;

	trunk.generate(height, segments, startingRadius, endRadius, 0, 10, -0.2, 0.2, -0.2, 0.2, seed);

	root->addChild(trunk.getRoot());

	//Adding branches
	float branchStart = height / 7;

	unsigned int branchAmount = 25;
	float branchY = branchStart + Generator::rand1d(10, seed) * (height - branchStart); //Calculating the position of the first branch

	for(unsigned int i = 0; i < branchAmount; i++)
	{
		//Selecting a position for the branch
		branchY = branchStart + Generator::rand1d(branchY, seed) * (height - (height / 6) - branchStart);

		osg::Vec3 branchPos = trunk.getCenter(branchY);

		//Calculating the length of the branch
		float branchLenth = (1 - branchY / height) * (height / 2);
		int branchSegments = 3;

		//Calculating the target angle of the branch
		float angleY = M_PI * 2 * Generator::rand1d(branchY, seed);

		float targetX = cos(angleY);
		float targetY = 0.3;
		float targetZ = sin(angleY);
		//calculating the rotation of the branch
		osg::Quat rotation;
		rotation.makeRotate(osg::Vec3(0, 1, 0), osg::Vec3(targetX, targetY, targetZ));

		//osg::Vec3 position = osg::Vec3(0, branchY, 0);

		addBranch(branchPos, rotation, branchLenth, branchSegments, -0.2, 0.2, -0.2, 0.2, seed);
	}

	//Adding the leaves to the root object
	for(unsigned int i = 0; i < branches.size(); i++)
	{
		Branch* branch = &branches.at(i);
		branch->addLeaves(1, 2, 2, 1, 1, 0.1, 1);
	}
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

	root->addChild(branch.getRoot());

	branches.push_back(branch);
}