#ifndef TERRAIN_H
#define TERRAIN_H

#include "Generator.h"
#include "ShaderObject.h"

#include <iostream>
#include <stdlib.h>

#include <deque>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture>
#include <osg/Image>
#include <osgUtil/SmoothingVisitor>

#define T_CHUNK_SIZE 32

class TerrainChunk
{
	public:
		void create(int x, int z, int sizeX, int sizeZ); ///Create a new chunk at x, z that has sizeX * sizeZ vertecies
		void destroy();

		void setShader(osg::Program* shaderProgram);

		//osg::PositionAttitudeTransform* getRoot();
		osg::Group* getRoot();
		osg::Geode* getGeode();
	private:
		int x;
		int z;

		float sizeX;
		float sizeZ;

		osg::Geode* geode;
		osg::Geometry* geometry;
		osg::PositionAttitudeTransform* posTransform;
		osg::Group* root;

		osg::Program* shaderProgram;
		osg::StateSet* state;
};

class Terrain
{
	public:
		Terrain();
		virtual ~Terrain();

		void createAround(float x, float z);
		void updateAround(float x, float z);
		void loadShader(std::string vert, std::string frag);

		osg::Group* getGroup();
	protected:
	private:
		//std::map<int, std::map<int, TerrainChunk > > chunks;
		std::deque< TerrainChunk > chunks;

		osg::Group* root;

		ShaderObject shaderObj;
};

#endif // TERRAIN_H
