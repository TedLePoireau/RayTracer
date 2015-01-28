#pragma once
#include <list>
#include "Object3D.h"
#include "Light.h"
#include "Sphere3D.h"
#include "Triangle.h"
#include "Mesh.h"

class Scene3D
{
private:
	std::list<Sphere3D*> *spheres;
	std::list<Triangle*> *triangles;
	std::list<Mesh*> * meshs;
	std::list<Light*> *lights;
	int size_x, size_y;
public:
	Scene3D(unsigned int size_x, unsigned int size_y);
	void addLight(Light* light);
	void Scene3D::addSphere(Sphere3D* object);
	void Scene3D::addTriangle(Triangle* object);

	void print();
};

