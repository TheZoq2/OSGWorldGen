#include "leaf.h"

int leafAmount = 0;

Leaf::Leaf()
{
}

void Leaf::create(float width, float height, float centerX, float centerZ)
{
	leafAmount++;

	textureCoords = new osg::Vec2Array;
	//Setup the base class
	setupObject();

	this->width = width;
	this->height = height;

	this->billboard = new osg::Billboard;
	this->geometry = new osg::Geometry;
	this->vertecies = new osg::Vec3Array;

	billboard->addDrawable(geometry);
	billboard->setAxis(osg::Vec3(0, 1, 0));
	billboard->setMode(osg::Billboard::POINT_ROT_EYE);

	//Calculating the corner positions
	float x1 = - centerX;
	float z1 = - centerZ;
	float x2 = width - centerX;
	float z2 = height - centerZ;

	//Creating vertecies
	vertecies->push_back(osg::Vec3(x1, 0, z1));
	vertecies->push_back(osg::Vec3(x1, 0, z2));
	vertecies->push_back(osg::Vec3(x2, 0, z1));
	vertecies->push_back(osg::Vec3(x2, 0, z2));

	geometry->setVertexArray(vertecies);

	//Creating faces
	osg::DrawElementsUInt* face1 = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	face1->push_back(0);
	face1->push_back(1);
	face1->push_back(2);

	geometry->addPrimitiveSet(face1);

	osg::DrawElementsUInt* face2 = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	face2->push_back(2);
	face2->push_back(1);
	face2->push_back(3);

	geometry->addPrimitiveSet(face2);

	//Calculating texture coords
	textureCoords->push_back(osg::Vec2(0, 0));
	textureCoords->push_back(osg::Vec2(0, 1));
	textureCoords->push_back(osg::Vec2(1, 0));
	textureCoords->push_back(osg::Vec2(1, 1));

	geometry->setTexCoordArray(0, textureCoords);

	//Adding the billboard to the root of the object class
	root->addChild(billboard);
}

void Leaf::setStateSet(osg::StateSet *stateSet)
{
	root->setStateSet(stateSet);
}
