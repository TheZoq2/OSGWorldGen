#include "object.h"

Object::Object()
{
}

void Object::setPosition(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	if(root != NULL)
	{
		root->setPosition(osg::Vec3(x, y, z));
	}
}

osg::PositionAttitudeTransform* Object::getRoot()
{
	return root;
}

void Object::setupObject()
{
	root = new osg::PositionAttitudeTransform;
}
