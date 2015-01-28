#include "Sphere3D.h"



Sphere3D::Sphere3D(float x, float y, float z, float rayon) :
	Object3D(x, y, z), rayon(rayon) {}


Sphere3D::~Sphere3D(void)
{
}

bool Sphere3D::isHit(const Ray &r, float &t)
{
	// intersection rayon/sphere 
	vecteur dist = getPos() - r.start;
	float B = r.dir * dist;
	float D = B*B - dist * dist + rayon * rayon;
	if (D < 0.0f)
		return false;
	float t0 = B - sqrtf(D);
	float t1 = B + sqrtf(D);
	bool retvalue = false;
	if ((t0 > 0.1f) && (t0 < t))
	{
		t = t0;
		retvalue = true;
	}
	if ((t1 > 0.1f) && (t1 < t))
	{
		t = t1;
		retvalue = true;
	}
	return retvalue;
}

vecteur Sphere3D::getNormale(const point &intersect)
{
	vecteur n = intersect - getPos();
	float den = n*n;
	den = 1.0f / sqrtf(den);
	n = den * n;
	return n;
}
