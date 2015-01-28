#pragma once
#include <list>
#include "Triangle.h"
class Mesh
{
public:
	std::list<Triangle*> triangles;
	Mesh();
	~Mesh();
};

