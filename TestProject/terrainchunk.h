#ifndef TERRAINCHUNK_H
#define TERRAINCHUNK_H

#include "Generator.h"
#include "ShaderObject.h"
#include "tree.h"

#include <iostream>
#include <stdlib.h>

#include <deque>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture>
#include <osg/Image>
#include <osgUtil/SmoothingVisitor>

class TerrainChunk
{
	public:
		void create(int x, int z, int sizeX, int sizeZ); ///Create a new chunk at x, z that has sizeX * sizeZ vertecies
		void updateAround(float xPos, float yPos, float zPos);
		void destroy();

		void setShader(osg::Program* shaderProgram);
		void setScale(float scale);

		//osg::PositionAttitudeTransform* getRoot();
		osg::Group* getRoot();
		osg::Geode* getGeode();
	private:
		int x;
		int z;

		float sizeX;
		float sizeZ;

		float scale;

		osg::Geode* geode;
		osg::Geometry* geometry;
		osg::PositionAttitudeTransform* posTransform;
		osg::Group* root;

		osg::Program* shaderProgram;
		osg::StateSet* state;

		std::vector<Tree> trees;
};

#endif // TERRAINCHUNK_H
