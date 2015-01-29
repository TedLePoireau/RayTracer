#pragma once
#include <string>
#include "Scene3D.h"
class RayTracer
{
private:
	
public:
	Scene3D* scene;
	RayTracer(std::string path);
	bool draw(char* outputName);
	~RayTracer(void);
	int main(void);
};

