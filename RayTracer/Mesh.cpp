#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <string>

#include "boost\algorithm\string.hpp"
#include <vector>


Mesh::Mesh(float pos_x, float pos_y, float pos_z, int material, float scale, std::string path_to_obj)
	: pos_x(pos_x), pos_y(pos_y), pos_z(pos_z), material(material), scale(scale)
{
	std::ifstream in(path_to_obj);
	std::string line;
	bool has_normals = false;
	while (std::getline(in, line))
	{
		if (line[0] == 'v' && line[1] == 'n')
		{
			has_normals = true;
			std::vector<std::string> strs;
			boost::split(strs, line, boost::is_any_of("\t "));
			vecteur p = { std::stof(strs[1]),
						std::stof(strs[2]),
						std::stof(strs[3])};
			normals.push_back(p);
		}
		if (line[0] == 'v')
		{
			std::vector<std::string> strs;
			boost::split(strs, line, boost::is_any_of("\t "));
			point p = { std::stof(strs[1]) * scale + pos_x, 
						std::stof(strs[2]) * scale  + pos_y,
						std::stof(strs[3]) * scale  + pos_z};
			points.push_back(p);
		}
		
		if (line[0] == 'f')
		{
			if (has_normals)
			{
				int p1=0, p2=0, p3=0;
				int n1=0, n2=0, n3=0;
				sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d", &p1, &n1, &p2, &n2, &p3, &n3);
				Triangle *t = new Triangle(points[p1 - 1],
					points[p2 - 1],
					points[p3 - 1],
					normals[n1-1]);
				t->material = material;
				triangles.push_back(t);
			}
			else
			{
				std::vector<std::string> strs;
				boost::split(strs, line, boost::is_any_of("\t "));
				Triangle *t = new Triangle(points[std::stoi(strs[1]) - 1],
					points[std::stoi(strs[2]) - 1],
					points[std::stoi(strs[3]) - 1]
					);
				triangles.push_back(t);
			}
		}
	}

}


Mesh::~Mesh()
{
}
