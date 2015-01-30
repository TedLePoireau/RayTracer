#pragma once
#include <list>
#include <vector>
#include "Triangle.h"
#include "Sphere3D.h"
class Mesh
{
public:
	std::vector<point> points;
	std::vector<vecteur> normals;
	std::list<Triangle*> triangles;
	float pos_x;
	float pos_y;
	float pos_z;
	float scale;
	int material;
	Sphere3D *bound;
	float dist(point p1, point p2);
	Mesh(float pos_x, float pos_y, float pos_z, int material, float scale, std::string path_to_obj);
	~Mesh();
};

