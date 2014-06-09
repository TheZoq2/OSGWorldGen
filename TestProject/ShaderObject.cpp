#include "ShaderObject.h"

ShaderObject::ShaderObject()
{
	loaded = false;
}
ShaderObject::ShaderObject(std::string vertName, std::string fragName)
{
	/*this->vertName = vertName;
	this->fragName = fragName;

	loaded = true;

	vertShader = new osg::Shader(osg::Shader::VERTEX);
	fragShader = new osg::Shader(osg::Shader::FRAGMENT);

	//Loading the vertex shader
	bool vertLoaded = loadShader(vertShader, vertName);
	if(vertLoaded == false)
	{
		loaded = false;
	}

	//Loading the fragment shader
	bool fragLoaded = loadShader(fragShader, fragName);
	if(fragLoaded == false)
	{
		loaded = false;
	}

	//Creating the shader
	program = new osg::Program;
	program->addShader(vertShader);
	program->addShader(fragShader);*/

	load(vertName, fragName);
}
void ShaderObject::load(std::string vertName, std::string fragName)
{
	this->vertName = vertName;
	this->fragName = fragName;

	loaded = true;

	vertShader = new osg::Shader(osg::Shader::VERTEX);
	fragShader = new osg::Shader(osg::Shader::FRAGMENT);

	//Loading the vertex shader
	bool vertLoaded = loadShader(vertShader, vertName);
	if(vertLoaded == false)
	{
		loaded = false;
	}

	//Loading the fragment shader
	bool fragLoaded = loadShader(fragShader, fragName);
	if(fragLoaded == false)
	{
		loaded = false;
	}

	//Creating the shader
	program = new osg::Program();
	program->addShader(vertShader);
	program->addShader(fragShader);
}

bool ShaderObject::loadShader(osg::Shader* obj, std::string filename)
{
	std::string fqFileName = osgDB::findDataFile(filename);

	if(fqFileName.length() == 0)
	{
		std::cout << "Shader: " << filename << " not found" << std::endl;
	}
	bool sucess = obj->loadShaderSourceFromFile(fqFileName.c_str());
	if(sucess == false)
	{
		std::cout << "Failed to load shader" << filename << std::endl;
	}

	return sucess;
}

osg::Program* ShaderObject::getProgram()
{
	return program;
}
bool ShaderObject::getLoaded()
{
	return loaded;
}
