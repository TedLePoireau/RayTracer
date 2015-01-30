#include "RayTracer.h"
#include <iostream>
#include "Scene3D.h"
#include "utility.h"
#include <Windows.h>

int main(int argc, char* argv[])
{

	RayTracer raytracer(argv[1]);
	Scene3D *scene = raytracer.scene;
	
	raytracer.draw("C:\\Users\\Nicolas\\goodmdr.tga");
	std::getchar();
	std::exit(0);
}