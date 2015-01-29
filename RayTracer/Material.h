#pragma once
class Material
{
public:
	int red;
	int green;
	int blue;

	float reflection;
	Material(int red, int green, int blue, float reflection);
	~Material();
};

