#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <string>
#include "boost\algorithm\string.hpp"
#include <vector>

Mesh::Mesh()
{
}

Mesh::Mesh(std::string path_to_obj)
{
	std::ifstream in(path_to_obj);
	std::string line;
	while (std::getline(in, line))
	{
		if (line[0] == 'v')
		{
			std::vector<std::string> strs;
			boost::split(strs, line, boost::is_any_of("\t "));
			point p = { std::stof(strs[1]), 
						std::stof(strs[2]),
						std::stof(strs[3])};
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
