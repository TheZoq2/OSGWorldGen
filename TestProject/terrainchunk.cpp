#include "terrainchunk.h"

void TerrainChunk::create(int x, int z,  int sizeX, int sizeZ)
{
	float seed = 12.256126;
	if(scale == 0)
	{
		scale = 1;
	}
	//int detailLevel = 2;
	if(sizeX < 1 || sizeZ < 1)
	{
		std::cout << "Failed to generate chunk, sizeX or sizeZ can not be 0";
		return;
	}

	destroy(); //Destroy the previous chunk to avoid duplication and other nasty things

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
			float pointHeight = Generator::getTerrainHeight(x + xVert, z + zVert, seed);

			pointHeight = pointHeight * scale;

			vertecies->push_back(osg::Vec3(xVert * scale, pointHeight, zVert * scale));

			/*r = (rand() % 255) / 255.0;
			g = (rand() % 255) / 255.0;
			b = (rand() % 255) / 255.0;*/

			float r = 1;
			float g = 1;
			float b = 1;

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
	posTransform->setPosition(osg::Vec3(x * scale, 0, z * scale));

	//adding the pos transform to the root node
	root->addChild(posTransform);

	state = new osg::StateSet();
	root->setStateSet(state);

	//Calculating normals
	osgUtil::SmoothingVisitor sv;
	root->accept(sv);

	unsigned int treeAmount = 8;
	//Creating trees
	for(unsigned int i = 0; i < treeAmount; i++)
	{
		//Selecting a random position for the tree
		float xPos = sizeX * Generator::rand2d(x * (i + 10), z, seed);
		float zPos = sizeZ * Generator::rand2d(x, z * (i + 10), seed);

		float yPos = Generator::getTerrainHeight(xPos + x, zPos + z, seed);

		float treeHeight = 10 + 10 * Generator::rand2d(xPos * i, zPos * i, seed);

		Tree tree;
		tree.generateFir(treeHeight, 10, Generator::rand2d(xPos, zPos, seed), 10, 0.4);

		tree.setPosition(xPos * scale, yPos * scale, zPos * scale);

		posTransform->addChild(tree.getRoot());

		trees.push_back(tree);
	}
//	std::cout << "Tree amount: " << treeAmount << std::endl;
}
void TerrainChunk::updateAround(float xPos, float yPos, float zPos)
{
	//Updating the LOD of all objects
	for(unsigned int i = 0; i < trees.size(); i++)
	{
		Tree* tree = &trees.at(i);
		float xDist = tree->getX() + x - xPos;
		float yDist = tree->getY() - yPos;
		float zDist = tree->getZ() + z - zPos;

		float dist = sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2));

		if(dist < 100)
		{
			tree->setLodLevel(0);
		}
		else
		{
			tree->setLodLevel(1);
		}
	}
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
void TerrainChunk::setScale(float scale)
{
	this->scale = scale;
}

osg::Geode* TerrainChunk::getGeode()
{
	return geode;
}

osg::Group* TerrainChunk::getRoot()
{
	return root;
}
