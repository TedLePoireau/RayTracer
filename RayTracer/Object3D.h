#pragma once
#include <tuple>
#include "utility.h"

class Object3D
{
private:
	point pos;
public:
	Object3D (float x, float y, float z);
	Object3D(point &p);
	virtual bool isHit(const ray &r, float &t) = 0;
	point getPos();
};