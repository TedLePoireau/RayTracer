#include "RayTracer.h"
#include <fstream>
#include "Scene3DParser.h"
#include <algorithm>
#include <boost/progress.hpp>
#include "tbb\include\tbb\parallel_for.h"
#include "tbb\include\tbb\blocked_range2d.h"
RayTracer::RayTracer(std::string path) 
{

	Scene3DParser* scene_parser = new Scene3DParser(path);
	scene = scene_parser->parse();
	image = new point*[scene->size_x];
	for (int i = 0; i < scene->size_x; ++i)
		image[i] = new point[scene->size_y];

}

bool RayTracer::draw(char* outputName)
{

	boost::progress_timer timer;
	imageFile = new std::ofstream(outputName, std::ios_base::binary);
	if (!imageFile)
		return false;
	// Ajout du header TGA
	imageFile->put(0).put(0);
	imageFile->put(2);        /* RGB non compresse */

	imageFile->put(0).put(0);
	imageFile->put(0).put(0);
	imageFile->put(0);

	imageFile->put(0).put(0); /* origine X */
	imageFile->put(0).put(0); /* origine Y */

	imageFile->put((scene->size_x & 0x00FF)).put((scene->size_x & 0xFF00) / 256);
	imageFile->put((scene->size_y & 0x00FF)).put((scene->size_y & 0xFF00) / 256);
	imageFile->put(24);       /* 24 bit bitmap */
	imageFile->put(0);
	// fin du header TGA

	tbb::parallel_for(tbb::blocked_range2d<size_t, size_t>(0, scene->size_x - 1, 0, scene->size_y - 1), [=](const tbb::blocked_range2d<size_t, size_t>& r) {
		for (size_t i = r.rows().begin(); i != r.rows().end(); ++i)
		{
			for (size_t j = r.cols().begin(); j != r.cols().end(); ++j)
			{
				trace(i, j);
				
			}
		}
		
	});

	for (int y = 0; y < scene->size_y; ++y) 
		for (int x = 0; x < scene->size_x; ++x)
			imageFile->put((unsigned char)image[x][y].x).put((unsigned char)image[x][y].y).put((unsigned char)image[x][y].z);

	
}
void RayTracer::trace(int x, int y)
{
		float red = 0, green = 0, blue = 0;
		float coef = 1.0f;
		int level = 0;
		// lancer de rayon 
		Ray viewRay;
		/*viewRay.start= { 0.0f, 0.0f, 1.0f };
		viewRay.dir = { float(x), float(y), -10000.0f };*/
		point supersampling = { 0.0f, 0.0f, 0.0f };


		for (float yf = float(y); yf < (float)y + 1; yf += 0.5f)
		{
			for (float xf = float(x); xf < (float)x + 1; xf += 0.5f)
			{

			viewRay.start = { float(xf), float(yf), -10000.0f };
	
			viewRay.dir = { 0.0f, 0.0f, 1.0f };
		do
		{
			// recherche de l'intersection la plus proche
			float t = 20000.0f;
			float currentSphere_t = t, currentTriangle_t = t;
			Sphere3D *currentSphere = NULL;
			Triangle* currentTriangle = NULL;
			for (Sphere3D *s : *scene->spheres)
			{
				if (s->isHit(viewRay, t))
				{
					currentSphere_t = t;
					currentSphere = s;
				}
			}
			for (Triangle *tri : *scene->triangles)
			{
				if (tri->isHit(viewRay, t))
				{
					currentTriangle_t = t;
					currentTriangle = tri;
				}
			}

			for (Mesh *m : *scene->meshs)
			{
				for (Triangle *tri : m->triangles)
				{
					if (tri->isHit(viewRay, t))
					{
						currentTriangle_t = t;
						currentTriangle = tri;
					}
				}
			}

			if (currentSphere_t == 20000.0f && currentTriangle_t == 20000.0f)
				break;

			point newStart = viewRay.start + t * viewRay.dir;
			vecteur n;
			Material* currentMat;
			if (currentSphere_t < currentTriangle_t)
			{
				n = currentSphere->getNormale(newStart);
				currentMat = scene->materials->at(currentSphere->material);
			}
			else
			{
				n = currentTriangle->getNormale();
				currentMat = scene->materials->at(0);
			}


			// calcul de la valeur d'éclairement au point 
			for (Light *light : *scene->lights) {
				vecteur dist = light->pos - newStart;
				if (n * dist <= 0.0f)
					continue;
				float t = sqrtf(dist * dist);
				if (t <= 0.0f)
					continue;
				Ray lightRay;
				lightRay.start = newStart;
				lightRay.dir = (1 / t) * dist;
				// calcul des ombres 
				bool inShadow = false;
				for (Sphere3D* s : *scene->spheres) {
					if (s->isHit(lightRay, t)) {
						inShadow = true;
						break;
					} 
					
				}
					
				for (Triangle *tri : *scene->triangles)
				{
					if (tri->isHit(lightRay, t))
					{
						inShadow = true;
						break;
					}
				}
					
				for (Mesh *m : *scene->meshs)
				{
					for (Triangle *tri : m->triangles)
					{
						if (tri->isHit(lightRay, t))
						{
							inShadow = true;
							break;
						}
					}
				}
					
				if (!inShadow) {
					// lambert
					float lambert = (lightRay.dir * n) * coef;
					red += lambert * light->red * currentMat->red;
					green += lambert *  light->green * currentMat->green;
					blue += lambert * light->blue * currentMat->blue;
				}
			}

			// on itére sur la prochaine reflexion
			coef *= currentMat->reflection;
			float reflet = 2.0f * (viewRay.dir * n);
			viewRay.start = newStart;
			viewRay.dir = viewRay.dir - reflet * n;

			level++;
		} while ((coef > 0.0f) && (level < 10));
		vecteur tmp = { 1.0f - expf(blue - 1.0f), 1.0f - expf(green - 1.0f), 1.0f - expf(red * -1.0f) };
		supersampling = supersampling + (0.25f *tmp);
	}
	}
	image[x][y] = {		(unsigned char)std::min(supersampling.x*255.0f, 255.0f),
						(unsigned char)std::min(supersampling.y*255.0f, 255.0f),
						(unsigned char)std::min(supersampling.z*255.0f, 255.0f) };
		return ;
}


RayTracer::~RayTracer(void)
{
}