#include "lodobject.h"

void LODObject::setupLod(unsigned int levelAmount)
{
	root = new osg::PositionAttitudeTransform;

	for(unsigned int i = 0; i < levelAmount; i++)
	{
		levels.push_back(NULL);
	}

	this->currentLod = -1;
	this->levelAmount = levelAmount;
}

void LODObject::addLodObject(osg::Group *object, unsigned int level)
{
	levels.at(level) = object;
}

void LODObject::unsetLodObject(unsigned int level)
{

}

void LODObject::setLodLevel(int level)
{
	if(levels.at(level) != NULL)
	{
		root->addChild(levels.at(level));
	}
}
