#pragma once
#include <istream>
#include <iostream>

struct point {
	float x, y, z;
};

struct vecteur {
	float x, y, z;
};

vecteur Normalize(vecteur& v1);

point operator + (const point &p, const vecteur &v);

point operator - (const point&p, const vecteur &v);


vecteur operator - (const point&p1, const point &p2);
vecteur operator * (float c, const vecteur &v);

vecteur operator - (const vecteur&v1, const vecteur &v2);
vecteur operator ^ (const vecteur&v1, const vecteur &v2);
bool operator == (const vecteur&v1, const vecteur &v2);

float operator * (const vecteur&v1, const vecteur &v2);