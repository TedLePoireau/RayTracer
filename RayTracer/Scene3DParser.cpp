#include "Scene3DParser.h"
#include <fstream>
#include <iostream>

#include <cctype>
#include <string>
#include "Sphere3D.h"
#include "Triangle.h"
#include "boost\algorithm\string\split.hpp"
#include "boost\algorithm\string\classification.hpp"
#include <vector>


Scene3DParser::Scene3DParser(std::string path) :
	path(path) {}

Scene3D* Scene3DParser::parse()
{
	if (path.empty())
	{
		Scene3D *scene = new Scene3D(0, 0);
		return scene;
	}
	line_nb = 0;
	std::ifstream in(path);
	std::string line;
	Scene3D *scene = NULL;
	while (readline(in, line))
	{
		if (line.empty())
			continue;
		if (line.at(0) == '#')
			continue;

		if (line == "scene") { scene = parseScene(in); }
		else if (line == "light")		{ parseLight(in, scene); }
		else if (line == "sphere") 		{ parseSphere(in, scene); }
		else if (line == "triangle")	{ parseTriangle(in, scene); }
		else if (line == "mesh")		{ parseMesh(in, scene); }
		else if (line == "material")	{ parseMaterial(in, scene); }
		else if (line == "plane")		{ }
	}
	return scene;
}



Scene3D* Scene3DParser::parseScene(std::ifstream& in)
{
	std::string line;
	int size_x = -1, size_y = -1, distance = -1;
	readline(in, line);
	if (line != "{")
	{
		std::cout << "[ERROR] Missing \"{\" at line : " << line_nb << std::endl;
		std::exit(-1);
	}
	std::string command;
	while (readline(in, line))
	{
		if (line == "}")
			break;
		command = *get_command(line);
		if (command == "size_x") {	size_x = std::stoi(*get_parameter(line)); }
		else if (command == "size_y") {	size_y = std::stoi(*get_parameter(line)); }
		else if (command == "distance") { distance = std::stoi(*get_parameter(line));	}
		else
		{
			std::cerr << "[ERROR] Unrecognized parameter at line : " << line_nb << std::endl;
			std::exit(-1);
		}
	}
	if ((size_x < 0) || (size_y < 0) || (distance < 0))
	{
		std::cout << "[ERROR] Missing parameter in Scene at line : " << line_nb << std::endl;
		std::exit(-1);
	}

	Scene3D* scene = new Scene3D(size_x, size_y);
	return scene;
}

void Scene3DParser::parseMaterial(std::ifstream& in, Scene3D* scene)
{
	std::string line;
	float red = -1, green = -1, blue = -1;
	float reflection = -1;
	readline(in, line);
	if (line != "{")
	{
		std::cout << "[ERROR] Missing \"{\" at line : " << line_nb << std::endl;
		std::exit(-1);
	}
	std::string command;
	while (readline(in, line))
	{
		if (line == "}")
			break;
		command = *get_command(line);
		if (command == "red") { red = std::stof(*get_parameter(line)); }
		else if (command == "green") { green = std::stof(*get_parameter(line)); }
		else if (command == "blue") { blue = std::stof(*get_parameter(line)); }
		else if (command == "reflection") { reflection = std::stof(*get_parameter(line)); }
		else
		{
			std::cout << "[ERROR] Unrecognized parameter at line : " << line_nb << std::endl;
			std::exit(-1);
		}
	}
	if ((red < 0) || (green < 0) || (blue < 0) || (reflection < 0))
	{
		std::cout << "[ERROR] Missing parameter in Sphere at line : " << line_nb << std::endl;
		std::exit(-1);
	}

	Material *mat = new Material(red, green, blue, reflection);
	scene->addMaterial(mat);
	return;
}

void Scene3DParser::parseLight(std::ifstream& in, Scene3D* scene)
{
	std::string line;
	float red = -1, green = -1, blue = -1;
	float pos_x, pos_y, pos_z;

	readline(in, line);
	if (line != "{")
	{
		std::cout << "[ERROR] Missing \"{\" at line : " << line_nb << std::endl;
		std::exit(-1);
	}
	std::string command;
	while (readline(in, line))
	{
		if (line == "}")
			break;
		command = *get_command(line);
		if (command == "red") { red = std::stof(*get_parameter(line)); }
		else if (command == "green") { green = std::stof(*get_parameter(line)); }
		else if (command == "blue") { blue = std::stof(*get_parameter(line)); }
		else if (command == "pos_x") { pos_x = std::stof(*get_parameter(line)); }
		else if (command == "pos_y") { pos_y = std::stof(*get_parameter(line)); }
		else if (command == "pos_z") { pos_z = std::stof(*get_parameter(line)); }
		
		else
		{
			std::cout << "[ERROR] Unrecognized parameter at line : " << line_nb << std::endl;
			std::exit(-1);
		}
	}
	if ((red < 0) || (green < 0) || (blue < 0))
	{
		std::cout << "[ERROR] Missing parameter in Sphere at line : " << line_nb << std::endl;
		std::exit(-1);
	}

	Light *l = new Light();
	l->blue = blue;
	l->green = green;
	l->red = red;
	l->pos = { pos_x, pos_y, pos_z };
	scene->lights->push_front(l);
	return;
}

void Scene3DParser::parseSphere(std::ifstream& in, Scene3D* scene)
{
	std::string line;
	float pos_x = -1, pos_y = -1, pos_z = -1, rayon = -1;
	int material = 0;
	readline(in, line);
	if (line != "{")
	{
		std::cout << "[ERROR] Missing \"{\" at line : " << line_nb << std::endl;
		std::exit(-1);
	}
	std::string command;
	while (readline(in, line))
	{
		if (line == "}")
			break;
		command = *get_command(line);
		if (command == "pos_x") { pos_x = std::stof(*get_parameter(line)); } 
		else if (command == "pos_y") { pos_y = std::stof(*get_parameter(line)); }
		else if (command == "pos_z") { pos_z = std::stof(*get_parameter(line)); }
		else if (command == "rayon") { rayon = std::stof(*get_parameter(line)); }
		else if (command == "material") { material = std::stof(*get_parameter(line)); }
		else
		{
			std::cout << "[ERROR] Unrecognized parameter at line : " << line_nb << std::endl;
			std::exit(-1);
		}
	}
	if ((pos_x < 0) || (pos_y < 0) || (rayon < 0))
	{
		std::cout << "[ERROR] Missing parameter in Sphere at line : " << line_nb << std::endl;
		std::exit(-1);
	}
	
	Sphere3D* sphere = new Sphere3D(pos_x, pos_y, pos_z, rayon, material);
	scene->addSphere(sphere);
	return;
}
void Scene3DParser::parseMesh(std::ifstream& in, Scene3D* scene)
{
	float pos_x = -1, pos_y = -1, pos_z = -1, scale = 1;
	int material = 0;
	std::string line;
	std::string command;
	Mesh *mesh = NULL;
	readline(in, line);
	if (line != "{")
	{
		std::cout << "[ERROR] Missing \"{\" at line : " << line_nb << std::endl;
		std::exit(-1);
	}
	while (readline(in, line))
	{
		if (line == "}")
			break;
		command = *get_command(line);
		if (command == "pos_x") { pos_x = std::stof(*get_parameter(line)); }
		else if (command == "pos_y") { pos_y = std::stof(*get_parameter(line)); }
		else if (command == "pos_z") { pos_z = std::stof(*get_parameter(line)); }
		else if (command == "material") { material = std::stof(*get_parameter(line)); }
		else if (command == "scale") { scale = std::stof(*get_parameter(line)); }
		else if (command == "file") { mesh = new Mesh(pos_x, pos_y, pos_z, material, scale, *get_parameter(line)); }
		else
		{
			std::cout << "[ERROR] Unrecognized parameter at line : " << line_nb << std::endl;
			std::exit(-1);
		}
	}
	scene->addMesh(mesh);
	

	return;

}
void Scene3DParser::parseTriangle(std::ifstream& in, Scene3D* scene)
{
	std::string line;
	float pos_x = -1, pos_y = -1, pos_z = -1, rayon = -1;
	readline(in, line);
	if (line != "{")
	{
		std::cout << "[ERROR] Missing \"{\" at line : " << line_nb << std::endl;
		std::exit(-1);
	}
	point pts[3];
	for (int i = 0; i < 3; i++)
	{
		readline(in, line);
		std::vector<std::string> strs;
		boost::split(strs, line, boost::is_any_of("\t "));
		pts[i] = { std::stof(strs[0]), std::stof(strs[1]), std::stof(strs[2]) };
	}
		
	Triangle* triangle = new 	Triangle(pts[0], pts[1], pts[2]);

	scene->addTriangle(triangle);
	return;
}


bool Scene3DParser::readline(std::ifstream& in, std::string& line)
{
	if (!std::getline(in, line))
		return false;
	if (line.empty())
		return true;
	trim_string(line);
	line_nb++;
	return true;
}


void Scene3DParser::trim_string(std::string& s)
{
	auto it = s.begin(), end = s.end();
	end--;
	while ( (it != end) && ( (std::isspace(*it)) || (*it == '\t') ))
		it++;
	while ( (end != it) && std::isspace(*end) )
		end--;
	s.erase(++end, s.end());
	s.erase(s.begin(), it);

	return;
}

std::string* Scene3DParser::get_command(std::string& s)
{
	auto it = s.begin();
	auto end = s.end();
	while (it != end && *it != ':' && *it != ' ' && *it != '\t')
		it++;
	if (it == end)
	{
		std::cout << "[ERROR] Impossible to parse line : " << line_nb << std::endl;
		std::exit(-1);
	}
	std::string* cmd = new std::string(s.begin(), it);
	return cmd;
}

std::string* Scene3DParser::get_parameter(std::string& s)
{
	auto begin= s.begin();
	auto it = s.end();
	it--;
	while (it != begin && *it != ' ' && *it != '\t')
		it--;
	if (it == begin)
	{
		std::cout << "[ERROR] Impossible to parse line : " << line_nb << std::endl;
		std::exit(-1);
	}
	std::string* param = new std::string(++it, s.end());
	return param;
}

Scene3DParser::~Scene3DParser(void)
{
}
