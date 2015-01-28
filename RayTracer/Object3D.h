#pragma once
#include <tuple>

class Object3D
{
private:
	unsigned int x;
	unsigned int y;
	unsigned int z;
public:
	Object3D (unsigned int x, unsigned int y, unsigned int z);
	std::pair<int,int> getPos();


};