#include "Object3D.h"

Object3D::Object3D(unsigned int x, unsigned int y, unsigned int z) :
	x(x), y(y), z(z) {}

std::pair<int,int> Object3D::getPos() 
{
	return std::pair<int,int>(x, y);
}