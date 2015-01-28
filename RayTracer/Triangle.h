#pragma once
#include "Object3D.h"

class Triangle : Object3D
{
	vecteur u;
	vecteur v;
public:
	Triangle(point &A, point &B, point &C);
	~Triangle();
	virtual bool isHit(const ray &r, float &t);
	vecteur getU();
	vecteur getV();
};
