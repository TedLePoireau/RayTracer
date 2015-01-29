#pragma once
#include <list>
#include <vector>
#include "Triangle.h"
class Mesh
{
public:
	std::vector<point> points;
	std::list<Triangle*> triangles;
	float pos_x;
	float pos_y;
	float pos_z;
	int material;
	Mesh(float pos_x, float pos_y, float pos_z, int material, std::string path_to_obj);
	~Mesh();
};

