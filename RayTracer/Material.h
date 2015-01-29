#pragma once
class Material
{
public:
	float red;
	float green;
	float blue;

	float reflection;
	Material(float red, float green, float blue, float reflection);
	~Material();
};

