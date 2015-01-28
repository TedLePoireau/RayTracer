#include "utility.h"

point operator + (const point &p, const vecteur &v){
	point p2 = { p.x + v.x, p.y + v.y, p.z + v.z };
	return p2;
}

point operator - (const point&p, const vecteur &v){
	point p2 = { p.x - v.x, p.y - v.y, p.z - v.z };
	return p2;
}

vecteur operator - (const point&p1, const point &p2){
	vecteur v = { p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
	return v;
}

vecteur operator * (float c, const vecteur &v)
{
	vecteur v2 = { v.x *c, v.y * c, v.z * c };
	return v2;
}

vecteur operator - (const vecteur&v1, const vecteur &v2){
	vecteur v = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return v;
}

vecteur operator ^ (const vecteur&v1, const vecteur &v2){
	vecteur v = { v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y };
	return v;
}


float operator * (const vecteur&v1, const vecteur &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}