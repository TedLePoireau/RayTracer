#pragma once
#include <list>
#include <vector>
#include "Triangle.h"
class Mesh
{
public:
	std::vector<point> points;
	std::list<Triangle*> triangles;
	Mesh();
	Mesh(std::string path_to_obj);
	~Mesh();
};

