#ifndef TERRAIN_H
#define TERRAIN_H

#include "Generator.h"
#include "ShaderObject.h"
#include "terrainchunk.h"

#include <iostream>
#include <stdlib.h>

#include <deque>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture>
#include <osg/Image>
#include <osgUtil/SmoothingVisitor>

#include "tree.h"

#define T_CHUNK_SIZE 32

class Terrain
{
	public:
		Terrain();
		virtual ~Terrain();

		void createAround(float x, float z);
		void updateAround(float x, float y, float z);
		void loadShader(std::string vert, std::string frag);

		osg::Group* getGroup();

		void setScale(float scale);
	protected:
	private:
		//std::map<int, std::map<int, TerrainChunk > > chunks;
		std::deque< TerrainChunk > chunks;

		osg::Group* root;

		ShaderObject shaderObj;

		float scale;
};

#endif // TERRAIN_H
