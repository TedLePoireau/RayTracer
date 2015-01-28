#include "Scene3D.h"
#include <iostream>

Scene3D::Scene3D(unsigned int size_x, unsigned int size_y) :
	size_x(size_x), size_y(size_y)
{
	objects = new std::list<Object3D*>();
	lights = new std::list<Light*>();
}

void Scene3D::addLight(Light* light)
{
	lights->push_front(light);
}

void Scene3D::addObject3D(Object3D* object)
{
	objects->push_front(object);
}

void Scene3D::print()
{
	std::cout << "Objects :" << objects->size() << std::endl;
	return;
}


