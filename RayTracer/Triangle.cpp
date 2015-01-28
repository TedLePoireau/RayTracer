#include "Triangle.h"


Triangle::Triangle(point &A, point &B, point &C) :
Object3D(A) {
	u = B - A;
	v = C - A;
}


Triangle::~Triangle()
{
}

bool Triangle::isHit(const Ray &r, float &t)
{
		float D = -1 * (u^v)*r.dir;

		vecteur w = r.start - getPos();
		float a = -1 * (w^v) * r.dir / D;
		float b = -1 * (u^w) * r.dir / D;

		float evalT = (u^v)*w / D;

		if (a > 0 && b > 0 && (a + b) <= 1 && evalT < t)
		{
			t = (u^v)*w / D;
			return true;
		}
		else
			return false;
}
