#include "Object3D.h"

Object3D::Object3D(float x, float y, float z)
{
	point p;
	p.x = x;
	p.y = y;
	p.z = z;
	pos = p;
}
Object3D::Object3D(point &p){
	pos = p;
}


point Object3D::getPos() 
{
	return pos;
}
