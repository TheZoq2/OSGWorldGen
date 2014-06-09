#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include <string>
#include <iostream>

#include <osg/Shader>
//#include <osgDB/Export>
#include <osgDB/Archive>

class ShaderObject
{
public:
	ShaderObject();
	ShaderObject(std::string vertName, std::string fragName);

	void load(std::string vertName, std::string fragName);

	bool loadShader(osg::Shader* obj, std::string filename);

	osg::Program* getProgram();
	bool getLoaded();
private:
	bool loaded;

	osg::Program* program;
	osg::Shader* vertShader;
	osg::Shader* fragShader;

	std::string fragName;
	std::string vertName;
};

#endif // SHADEROBJECT_H
