#include "Scene3D.h"
#include <iostream>

Scene3D::Scene3D(unsigned int size_x, unsigned int size_y) :
	size_x(size_x), size_y(size_y)
{
	spheres = new std::list<Sphere3D*>();
	triangles = new std::list<Triangle*>();
	meshs = new std::list<Mesh*>();
	lights = new std::list<Light*>();
}

void Scene3D::addLight(Light* light)
{
	lights->push_front(light);
}

void Scene3D::addSphere(Sphere3D* object)
{
	spheres->push_front(object);
}

void Scene3D::addTriangle(Triangle* object)
{
	triangles->push_front(object);
}

void Scene3D::print()
{
	std::cout << "Sphere :" << spheres->size() << std::endl;
	return;
}


