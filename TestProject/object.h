#ifndef OBJECT_H
#define OBJECT_H

#include <osg/Geometry>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>

class Object
{
public:
	Object();

	void setPosition(float x, float y, float z);

	osg::PositionAttitudeTransform* getRoot();

	float getX();
	float getY();
	float getZ();
protected:
	void setupObject();

	osg::PositionAttitudeTransform* root;

	float x;
	float y;
	float z;
private:

};

#endif // PLANT_H
