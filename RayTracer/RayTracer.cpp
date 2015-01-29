#include "RayTracer.h"
#include <fstream>
#include "Scene3DParser.h"
#include <algorithm>
RayTracer::RayTracer(std::string path) 
{
	Scene3DParser* scene_parser = new Scene3DParser(path);
	scene = scene_parser->parse();
}

bool RayTracer::draw(char* outputName)
{
	std::ofstream imageFile(outputName, std::ios_base::binary);
	if (!imageFile)
		return false;
	// Ajout du header TGA
	imageFile.put(0).put(0);
	imageFile.put(2);        /* RGB non compresse */

	imageFile.put(0).put(0);
	imageFile.put(0).put(0);
	imageFile.put(0);

	imageFile.put(0).put(0); /* origine X */
	imageFile.put(0).put(0); /* origine Y */

	imageFile.put((scene->size_x & 0x00FF)).put((scene->size_x & 0xFF00) / 256);
	imageFile.put((scene->size_y & 0x00FF)).put((scene->size_y & 0xFF00) / 256);
	imageFile.put(24);       /* 24 bit bitmap */
	imageFile.put(0);
	// fin du header TGA

	// balayage 
	for (int y = 0; y < scene->size_y; ++y) {
		for (int x = 0; x < scene->size_x; ++x) {
			float red = 0, green = 0, blue = 0;
			float coef = 1.0f;
			int level = 0;
			// lancer de rayon 
			Ray viewRay;
			viewRay.start= { 0.0f, 0.0f, 1.0f };
			viewRay.dir = { float(x), float(y), -10000.0f };
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
				if (currentSphere_t < currentTriangle_t)
				{
					n = currentSphere->getNormale(newStart);
				}
				else
				{
					n = currentTriangle->getNormale();
				}

				Material* currentMat = scene->materials->front();

				// calcul de la valeur d'�clairement au point 
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
					if (!inShadow) {
						// lambert
						float lambert = (lightRay.dir * n) * coef;
						red += lambert * light->red * currentMat->red;
						green += lambert *  light->green * currentMat->green;
						blue += lambert * light->blue * currentMat->blue;
					}
				}

				// on it�re sur la prochaine reflexion
				coef *= currentMat->reflection;
				float reflet = 2.0f * (viewRay.dir * n);
				viewRay.start = newStart;
				viewRay.dir = viewRay.dir - reflet * n;

				level++;
			} while ((coef > 0.0f) && (level < 10));

			imageFile.put((unsigned char)std::min(blue*255.0f, 255.0f)).put((unsigned char)std::min(green*255.0f, 255.0f)).put((unsigned char)std::min(red*255.0f, 255.0f));
		}
	}
	return true;
}


RayTracer::~RayTracer(void)
{
}