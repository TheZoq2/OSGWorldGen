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
protected:
	void setupObject();

	osg::PositionAttitudeTransform* root;
private:
	float x;
	float y;
	float z;
};

#endif // PLANT_H
