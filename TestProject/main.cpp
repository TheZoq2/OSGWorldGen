#include <iostream>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>

#include "Terrain.h"
#include "branch.h"
#include "tree.h"
#include "leaf.h"

osg::Group* getTriangle();

int main()
{
	//Terrain terrain;

	//terrain.createAround(0, 0);

	//terrain.loadShader("../media/shaders/terrain.vert", "../media/shaders/terrain.frag");
	//TerrainChunk chunk;
	//chunk.create(0, 0, 128, 128);
	Tree tree;
	tree.generateFir(24, 10, 1.25215, 30, 0.4);
	tree.setLeafTexture("../media/img/Barr.png");

	//Creating a root object
	osg::Group* root = new osg::Group();

	//root->addChild(terrain.getGroup());
	root->addChild(tree.getRoot());
	root->addChild(getTriangle());

	osgViewer::Viewer viewer;

	viewer.setSceneData( root );
	viewer.run();

	return 0;
}

osg::Group* getTriangle()
{
	osg::Group* root = new osg::Group();
	osg::Geode* pyramidGeode = new osg::Geode;
	osg::Geometry* pyramidGeometry = new osg::Geometry;

	pyramidGeode->addDrawable(pyramidGeometry);
	root->addChild(pyramidGeode);

	osg::Vec3Array* pyramidVertices = new osg::Vec3Array;
	pyramidVertices->push_back(osg::Vec3(-0.5, 0, -0.5));
	pyramidVertices->push_back(osg::Vec3(0.5, 0, -0.5));
	pyramidVertices->push_back(osg::Vec3(0.5, 0, 0.5));
	pyramidVertices->push_back(osg::Vec3(-0.5, 0, 0.5));
	pyramidVertices->push_back(osg::Vec3(0, 1, 0));

	pyramidGeometry->setVertexArray(pyramidVertices);

	osg::DrawElementsUInt* pyramidBase = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	pyramidBase->push_back(3);
	pyramidBase->push_back(2);
	pyramidBase->push_back(1);
	pyramidBase->push_back(0);
	pyramidGeometry->addPrimitiveSet(pyramidBase);

	osg::DrawElementsUInt* pFace1 = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pFace1->push_back(1);
	pFace1->push_back(2);
	pFace1->push_back(4);
	pyramidGeometry->addPrimitiveSet(pFace1);

	osg::DrawElementsUInt* pFace2 = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pFace2->push_back(2);
	pFace2->push_back(3);
	pFace2->push_back(4);
	pyramidGeometry->addPrimitiveSet(pFace2);

	osg::DrawElementsUInt* pyramidFaceThree =
	  new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceThree->push_back(2);
	pyramidFaceThree->push_back(3);
	pyramidFaceThree->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceThree);

	osg::DrawElementsUInt* pyramidFaceFour =
	  new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceFour->push_back(3);
	pyramidFaceFour->push_back(0);
	pyramidFaceFour->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceFour);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	colors->push_back(osg::Vec4(1.0, 1.0, 0.0, 1.0));
	colors->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	colors->push_back(osg::Vec4(1.0, 0.0, 1.0, 1.0));
	colors->push_back(osg::Vec4(0.0, 1.0, 1.0, 1.0));

	pyramidGeometry->setColorArray(colors);
	pyramidGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	return root;
}

