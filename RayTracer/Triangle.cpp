#include "Triangle.h"


Triangle::Triangle(point &A, point &B, point &C) :
Object3D(A) {
	u = B - A;
	v = C - A;
	n = u^v;
}

Triangle::Triangle(point &A, point &B, point &C, vecteur normal) :
Object3D(A) {
	u = B - A;
	v = C - A;
	n = normal;
}


Triangle::~Triangle()
{
}

bool Triangle::isHit(const Ray &r, float &t)
{
		//float D = -1 * (u^v)*r.dir;

		//vecteur w = r.start - getPos();
		//float a = -1 * (w^v) * r.dir / D;
		//float b = -1 * (u^w) * r.dir / D;

		//float evalT = (u^v)*w / D;

		//if (a >=0 && b >= 0 && (a + b) <= 1 && evalT < t)
		//{
		//	t = (u^v)*w / D;
		//	return true;
		//}
		//else
		//	return false;



	
	vecteur P, Q, T;
	float EPSILON = 0.1f;
	float testval;
	float det, inv_det, param_u, param_v;




	P = r.dir ^ v;
	det = u * P;

	if (det > -EPSILON && det < EPSILON)
		return false;

	inv_det = 1.0f / det;
	T = r.start - getPos();

	param_u = T * P * inv_det;

	if (param_u < 0.0f || param_u > 1.0f)
		return false;


	Q = T ^ u;
	param_v = r.dir * Q * inv_det;

	if (param_v < 0.0f || param_u + param_v > 1.0f)
		return false;


	testval = v * Q * inv_det;
	if (testval > EPSILON && testval < t)
	{
		t = testval;
		return true;
	}
	return false;

}
vecteur Triangle::getNormale()
{
	return n;
}
