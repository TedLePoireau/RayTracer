#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <string>
#include "boost\algorithm\string.hpp"
#include <vector>


Mesh::Mesh(float pos_x, float pos_y, float pos_z, int material, std::string path_to_obj)
	: pos_x(pos_x), pos_y(pos_y), pos_z(pos_z), material(material)
{
	std::ifstream in(path_to_obj);
	std::string line;
	while (std::getline(in, line))
	{
		if (line[0] == 'v')
		{
			std::vector<std::string> strs;
			boost::split(strs, line, boost::is_any_of("\t "));
			point p = { std::stof(strs[1]) + pos_x, 
						std::stof(strs[2]) + pos_y,
						std::stof(strs[3]) + pos_z};
			points.push_back(p);
		}
		
		if (line[0] == 'f')
		{
			std::vector<std::string> strs;
			boost::split(strs, line, boost::is_any_of("\t "));
			Triangle *t = new Triangle(points[std::stoi(strs[1])-1],
				points[std::stoi(strs[2])-1],
				points[std::stoi(strs[3])-1]);
			triangles.push_back(t);
		}
	}

}


Mesh::~Mesh()
{
}
