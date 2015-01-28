#pragma once
#include "Object3D.h"

class Sphere3D : Object3D
{
	float rayon;
public:
	Sphere3D(float x, float y, float z, float rayon);
	~Sphere3D(void);
	virtual bool isHit(const Ray &r, float &t);
	vecteur getNormale(const point &intersect);
};

