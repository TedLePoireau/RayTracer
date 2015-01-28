#pragma once
#include <tuple>
#include "utility.h"
#include "Ray.h"

class Object3D
{
private:
	point pos;
public:
	Object3D (float x, float y, float z);
	Object3D(float x, float y, float z, int mat);
	Object3D(point &p);
	virtual bool isHit(const Ray &r, float &t) = 0;
	point getPos();
	int material = 0;
};