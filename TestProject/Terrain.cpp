#include "Terrain.h"

#include <osg/PolygonMode>

void TerrainChunk::create(int x, int z,  int sizeX, int sizeZ)
{
	//int detailLevel = 2;
	if(sizeX < 1 || sizeZ < 1)
	{
		std::cout << "Failed to generate chunk, sizeX or sizeZ can not be 0";
		return;
	}
	//destroy(); //Destroy the previous chunk to avoid duplication and other nasty things

	this->x = x;
	this->z = z;
	this->sizeX = sizeX;
	this->sizeZ = sizeZ;

	geode = new osg::Geode();
	geometry = new osg::Geometry();

	geode->addDrawable(geometry);

	osg::ref_ptr< osg::Vec3Array > vertecies = new osg::Vec3Array();
	//Color array
	osg::ref_ptr< osg::Vec4Array > colors = new osg::Vec4Array;

	for(float xVert = 0; xVert < sizeX; xVert++)
	{
		for(float zVert = 0; zVert < sizeZ; zVert++)
		{
			float heightSum = (75+25+12+7+3+2+1);

			float pointHeight = Generator::getPointHeight(x + xVert, z + zVert, 256) * 75;
			pointHeight = pointHeight + Generator::getPointHeight(x + xVert, z + zVert, 64) * 25;
			pointHeight = pointHeight + Generator::getPointHeight(x + xVert, z + zVert, 32) * 12;
			pointHeight = pointHeight + Generator::getPointHeight(x + xVert, z + zVert, 20) * 7;
			pointHeight = pointHeight + Generator::getPointHeight(x + xVert, z + zVert, 16) * 3;
			pointHeight = pointHeight + Generator::getPointHeight(x + xVert, z + zVert, 8) * 2;
			//pointHeight = pointHeight + Generator::getPointHeight(x + xVert, z + zVert, 4) * 1;

			//Smoothing terrain below
			float pointFact = pointHeight / (heightSum * 1.2);

			pointHeight = pointHeight * pointFact;

			vertecies->push_back(osg::Vec3(xVert, pointHeight, zVert));

			//Generating the color of the vertex
			float r = 1 - pointHeight / ((heightSum + 25));
			float g = 1;
			float b = 1 - pointHeight / (heightSum + 25);

			/*r = (rand() % 255) / 255.0;
			g = (rand() % 255) / 255.0;
			b = (rand() % 255) / 255.0;*/

			r = 1;
			g = 1;
			b = 1;

			colors->push_back(osg::Vec4(r, g, b, 1));
		}
	}

	geometry->setVertexArray(vertecies);


	//Creating faces
	for(unsigned int i = 0; i < vertecies->size() - sizeZ; i++)
	{
		if(i % sizeZ != (unsigned)(sizeZ - 1))
		{
			osg::DrawElementsUInt* face = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

			face->push_back(i);
			face->push_back(i + sizeZ);
			face->push_back(i + 1);

			geometry->addPrimitiveSet(face);
		}
	}
	for(unsigned int i = sizeZ; i < vertecies->size(); i++)
	{
		if(i % sizeZ != sizeZ - 1) //Preventing weird faces and other nasty things
		{
			if(i < vertecies->size())
			{
				osg::DrawElementsUInt* face = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

				face->push_back(i);
				face->push_back(i + 1);
				face->push_back(i - sizeZ + 1);

				geometry->addPrimitiveSet(face);
			}
		}
	}

	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//root = new osg::PositionAttitudeTransform();
	//root->setPosition(osg::Vec3(x, 0, z));
	root = new osg::Group;

	//Adding the geode to the posTransform;
	posTransform = new osg::PositionAttitudeTransform;
	posTransform->addChild(geode);

	//Transforming the position
	posTransform->setPosition(osg::Vec3(x, 0, z));

	//adding the pos transform to the root node
	root->addChild(posTransform);

	state = new osg::StateSet();
	root->setStateSet(state);

	//Calculating normals
	osgUtil::SmoothingVisitor sv;
	root->accept(sv);
}
void TerrainChunk::destroy()
{

}

void TerrainChunk::setShader(osg::Program* shaderProgram)
{
	this->shaderProgram = shaderProgram;

	state->setAttributeAndModes(shaderProgram, osg::StateAttribute::ON);
	/*osg::PolygonMode* mode = new osg::PolygonMode;
	mode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	state->setAttributeAndModes(mode, osg::StateAttribute::ON);*/
}

osg::Geode* TerrainChunk::getGeode()
{
	return geode;
}

osg::Group* TerrainChunk::getRoot()
{
	return root;
}

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

	int chunkAmountX = 20;
	int chunkAmountZ = 20;

	for(int xPos = - T_CHUNK_SIZE * chunkAmountX; xPos < T_CHUNK_SIZE * chunkAmountX; xPos = xPos + T_CHUNK_SIZE - 1)
	{
		std::cout << "Generating X: " << xPos << std::endl;
		for(int zPos = - T_CHUNK_SIZE * chunkAmountZ; zPos < T_CHUNK_SIZE * chunkAmountZ; zPos = zPos + T_CHUNK_SIZE - 1)
		{
			TerrainChunk chunk;

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
void Terrain::updateAround(float x, float z)
{

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
