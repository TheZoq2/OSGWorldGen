#include "Terrain.h"

#include <osg/PolygonMode>


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Terrain::Terrain()
{
	//ctor

	root = new osg::Group;
}

Terrain::~Terrain()
{
	//dtor

	//delete root;
}

void Terrain::createAround(float x, float z)
{
	std::cout << "Done" << std::endl;

	int chunkAmountX = 10;
	int chunkAmountZ = 10;

	for(int xPos = - T_CHUNK_SIZE * chunkAmountX; xPos < T_CHUNK_SIZE * chunkAmountX; xPos = xPos + T_CHUNK_SIZE - 1)
	{
		std::cout << "Generating X: " << xPos << std::endl;
		for(int zPos = - T_CHUNK_SIZE * chunkAmountZ; zPos < T_CHUNK_SIZE * chunkAmountZ; zPos = zPos + T_CHUNK_SIZE - 1)
		{
			TerrainChunk chunk;
			chunk.setScale(scale);

			//chunk.create(x, z, T_CHUNK_SIZE, T_CHUNK_SIZE);
			//chunks.push_back(*chunk);

			//chunks.end()->create(xPos, zPos, T_CHUNK_SIZE, T_CHUNK_SIZE);

			chunk.create(x + xPos, z + zPos, T_CHUNK_SIZE, T_CHUNK_SIZE);

			root->addChild(chunk.getRoot());

			chunks.push_back(chunk);
		}
	}

	std::cout << "Generation done" << std::endl;
}
void Terrain::updateAround(float x, float y, float z)
{
	//Looping thru all the chunks and updating them
	for(unsigned int i = 0; i < chunks.size(); i++)
	{
		TerrainChunk* chunk = &chunks.at(i);

		chunk->updateAround(x, y, z);
	}
}

void Terrain::loadShader(std::string vert, std::string frag)
{
	shaderObj.load(vert, frag);

	//If the shader was loaded propperly
	if(shaderObj.getLoaded() == true)
	{
		for(unsigned int i = 0; i < chunks.size(); i++)
		{
			chunks.at(i).setShader(shaderObj.getProgram());
		}
	}
}

osg::Group* Terrain::getGroup()
{
	return root;
}

void Terrain::setScale(float scale)
{
	this->scale = scale;
}
