#pragma once
#include <tuple>
#include "utility.h"

class Object3D
{
private:
	unsigned int x;
	unsigned int y;
	unsigned int z;
public:
	Object3D (unsigned int x, unsigned int y, unsigned int z);
	virtual bool isHit(const ray &r, float &t) = 0;
	std::pair<int,int> getPos();


};