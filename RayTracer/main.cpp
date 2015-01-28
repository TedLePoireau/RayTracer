#include "RayTracer.h"
#include <iostream>
#include "Scene3D.h"
#include "utility.h"
int main(int argc, char* argv[])
{
	RayTracer raytracer(argv[1]);
	Scene3D *scene = raytracer.scene;
	scene->print();
	std::getchar();
	std::exit(0);
}