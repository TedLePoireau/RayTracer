#pragma once
#include <list>
#include <vector>
#include "Object3D.h"
#include "Light.h"
#include "Sphere3D.h"
#include "Triangle.h"
#include "Material.h"
#include "Mesh.h"

class Scene3D
{
private:

	
public:
	std::list<Sphere3D*> *spheres;
	std::list<Triangle*> *triangles;
	std::list<Mesh*> * meshs;
	std::list<Light*> *lights;
	std::vector<Material*> *materials;
	Scene3D(unsigned int size_x, unsigned int size_y);
	void addLight(Light* light);
	void addSphere(Sphere3D* object);
	void addTriangle(Triangle* object);
	void addMesh(Mesh* object);
	void addMaterial(Material* mat);
	void print();
	int size_x, size_y;
};

