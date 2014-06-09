#ifndef BRANCH_H
#define BRANCH_H

#include<math.h>
#include<cmath>
#include<vector>

#include<osg/Geode>
#include<osg/Geometry>
#include<osg/StateSet>
#include<osg/PolygonMode>
#include<osg/Quat>
#include<osg/PositionAttitudeTransform>

#include "Generator.h"
#include "leaf.h"

class Branch
{
public:
	Branch();

	///Generate a branc. Length is the length of the branch, segments is the amount of segments.
	/// Max/min bend is the max amount that the branc can be bent for each new segment
	/// Start and end radius is the radius of the end points
	/// Radius diff is how much each vertex in a segment is allowed to be "off" from the radius
	/// ringAmount is how many vertecies are on each "ring"
	void generate(float length, unsigned int segments, float startRadius, float endRadius, float radiusDiff, unsigned int ringAmount, float minBendX, float maxBendX, float minBendZ, float maxBendZ, float seed);

	void setRotation(osg::Quat rotation);
	void setPosition(osg::Vec3 position);

	osg::Geode* getGeode();
	osg::PositionAttitudeTransform* getRoot();
	osg::Vec3 getCenter(float y);

	void addLeaves(float leafAmount, float width, float height, float cX, float cZ, float start, float end);
private:
	osg::Quat* quat;
	osg::PositionAttitudeTransform* rootTransform;

	osg::Geode* geode;
	osg::Geometry* geometry;

	osg::Vec3Array* vertecies;

	osg::Vec3Array* segmentPos;

	float length;
	int segments;
	float startRadius;
	float endRadius;
	float radiusDiff;
	int ringAmount;
	float minBendX;
	float maxBendX;
	float minBendZ;
	float maxBendZ;

	float seed;

	osg::Quat rotation;
	osg::Vec3 position;

	std::vector<Leaf> leaves;
};

#endif // BRANCH_H
