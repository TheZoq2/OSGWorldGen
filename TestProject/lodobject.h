#ifndef LODOBJECT_H
#define LODOBJECT_H

#include "object.h"

#include <iostream>
#include <vector>

class LODObject : public Object
{
public:
	//LODObject(unsigned int levelAmount);
	void setupLod(unsigned int levelAmount);

	void setLodLevel(int level);
protected:
	void addLodObject(osg::Group* object, unsigned int level);

	void unsetLodObject(unsigned int level);
private:
	std::vector<osg::Group*> levels;

	int levelAmount;
	int currentLod;
};

#endif // LODOBJECT_H
