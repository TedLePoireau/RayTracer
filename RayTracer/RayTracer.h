#pragma once
#include <string>
#include <iostream>
#include "Scene3D.h"
class RayTracer
{
private:
	
public:
	Scene3D* scene;
	std::ofstream *imageFile;
	point** image;
	void trace(int x, int y);
	RayTracer(std::string path);
	bool draw(char* outputName);
	~RayTracer(void);
	int main(void);
};

