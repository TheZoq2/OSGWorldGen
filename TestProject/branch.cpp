#include "branch.h"

int branchAmount = 0;

Branch::Branch()
{
}

void Branch::generate(float length, unsigned int segments, float startRadius, float endRadius, float radiusDiff, unsigned int ringAmount, float minBendX, float maxBendX, float minBendZ, float maxBendZ, float seed)
{
	branchAmount++;

	this->seed = seed;

	this->length = length;
	this->segments = segments;
	this->startRadius = startRadius;
	this->endRadius = endRadius;
	this->radiusDiff = radiusDiff;
	this->ringAmount = ringAmount;

	this->minBendX = minBendX;
	this->maxBendX = maxBendX;
	this->minBendZ = minBendZ;
	this->maxBendZ = maxBendZ;

	//Preparing the geode and geometry
	geode = new osg::Geode;
	geometry = new osg::Geometry;
	segmentPos = new osg::Vec3Array;

	geode->addDrawable(geometry);

	vertecies = new osg::Vec3Array;

	//Calculating the length of each segment
	float segmentLength = length / segments;

	float segmentAngleX = 0;
	float segmentAngleZ = 0;
	for(unsigned int i = 0; i < segments; i++)
	{
		float yPos = i*segmentLength;
		//Calculating the new angle of the segment
		segmentAngleX += Generator::rand1d(yPos, seed) * (std::abs(minBendX) + std::abs(maxBendX) - std::abs(minBendX));
		segmentAngleZ += Generator::rand1d(yPos, seed) * (std::abs(minBendZ) + std::abs(maxBendZ) - std::abs(minBendZ));

		//Calculating the new x and z centerpoints
		float xCenter = sin(segmentAngleX) * segmentLength;
		float zCenter = sin(segmentAngleZ) * segmentLength;

		//Calculating the angle of each "ring vertex"
		float ringAngle = M_PI * 2 / (ringAmount); //+1 because vertecies are connected

		//Calculating the radius of this segment
		float topDist = yPos / length;
		float ringRadius = startRadius + (endRadius - startRadius) * topDist;
		for(unsigned int n = 0; n < ringAmount; n++)
		{
			float ringX = xCenter + sin(ringAngle * n) * ringRadius;
			float ringZ = zCenter + cos(ringAngle * n) * ringRadius;

			//Creating a vertex
			vertecies->push_back(osg::Vec3(ringX, yPos, ringZ));
		}

		//Saving the position of the branch
		segmentPos->push_back(osg::Vec3(xCenter, yPos, zCenter));
	}

	//Creating faces
	for(unsigned int i = 0; i < segments - 1; i++)
	{
		for(unsigned int n = 0; n < ringAmount; n++)
		{
			int vert1 = i * ringAmount + n; //0
			int vert2 = (i + 1) * ringAmount + n; //0 + i
			int vert3 = (i + 1) * ringAmount + n - 1;

			if((unsigned int)vert3 < vertecies->size())
			{
				osg::DrawElementsUInt* face = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

				face->push_back(vert1);
				face->push_back(vert2);
				face->push_back(vert3);

				geometry->addPrimitiveSet(face);
			}

			vert1 = i * ringAmount + n;
			vert2 = i * ringAmount + n - 1;
			vert3 = (i + 1) * ringAmount + n - 1;
			if(vert2 >= 0)
			{
				osg::DrawElementsUInt* face = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

				face->push_back(vert1);
				face->push_back(vert2);
				face->push_back(vert3);

				geometry->addPrimitiveSet(face);
			}
		}
	}

	geometry->setVertexArray(vertecies);

	/*osg::PolygonMode* mode = new osg::PolygonMode;
	osg::StateSet* stateSet = new osg::StateSet;
	mode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

	stateSet->setAttributeAndModes(mode);*/

	//geode->setStateSet(stateSet);

	quat = new osg::Quat;
	rootTransform = new osg::PositionAttitudeTransform;
	rootTransform->addChild(geode);

	//Calculating normals
	osgUtil::SmoothingVisitor sv;
	rootTransform->accept(sv);
}

void Branch::setRotation(osg::Quat rotation)
{
	this->rotation = rotation;

	rootTransform->setAttitude(rotation);
}
void Branch::setPosition(osg::Vec3 position)
{
	this->position = position;

	rootTransform->setPosition(position);
}

osg::Geode* Branch::getGeode()
{
	return this->geode;
}
osg::PositionAttitudeTransform* Branch::getRoot()
{
	return this->rootTransform;
}
osg::Vec3 Branch::getCenter(float y)
{
	float segLength = length / segments; //The height diffirence between 2 segments

	//Calculating which 2 segments to look at
	int lowerSegment = floor(y / segLength);
	int upperSegment = lowerSegment + 1;

	osg::Vec3 pos;
	//Making sure both segments are inside the segments
	if(lowerSegment >= 0 && upperSegment < (int) segmentPos->size())
	{
		float lowerX = segmentPos->at(lowerSegment).x();
		float lowerZ = segmentPos->at(lowerSegment).z();

		float upperX = segmentPos->at(upperSegment).x();
		float upperZ = segmentPos->at(upperSegment).z();

		float xDiff = upperX - lowerX;
		float zDiff = upperZ - lowerZ;

		float yDiff = y - (lowerSegment * segLength);
		float yFact = yDiff / segLength;

		float posX = xDiff * yFact + lowerX;
		float posZ = zDiff * yFact + lowerZ;
		pos.set(posX, y, posZ);
	}

	return pos;
}

void Branch::addLeaves(float density, float width, float height, float cX, float cZ, float start, float end)
{
	float startPoint = length * start;
	float endPoint =  length * end;

	unsigned int leafAmount = ceil((endPoint - startPoint) * density);

	float leafY = endPoint * Generator::rand1d(length, seed) - startPoint;
	for(unsigned int i = 0; i < leafAmount; i++)
	{
		Leaf leaf;
		leaf.create(width, height, cX, cZ);

		//Calculating the position of the leaf
		leafY = Generator::rand1d(leafY, seed) * (endPoint - startPoint) + startPoint;

		//Actual position
		osg::Vec3 pos = getCenter(leafY);

		//Randomising the position of the leaf
		pos.set(
					pos.x() + Generator::rand1d(leafY, seed) * 1.5 - 0.75,
					pos.y(),
					pos.z() + Generator::rand1d(leafY, seed) * 1.5 - 0.75
				);

		if(pos.y() == leafY)
		{
			leaf.setPosition(pos.x(), pos.y(), pos.z());

			leaves.push_back(leaf);

			rootTransform->addChild(leaf.getRoot());
		}
	}
}
void Branch::setLeafStateSet(osg::StateSet* stateSet)
{
	for(unsigned int i = 0; i < leaves.size(); i++)
	{
		leaves.at(i).setStateSet(stateSet);
	}
}
