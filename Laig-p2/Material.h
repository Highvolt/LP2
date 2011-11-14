#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>

#ifdef __APPLE__
#include <GLUI/GLUI.h>
#else
#include <gl/glui.h>
#endif

using namespace std;

class Material{
	string id;
	float mat_shininess[1];
	float mat_specular[4];
	float mat_diffuse[4];
	float mat_ambient[4];
	float mat_emission[4];
	
public:
	Material(string id);
	string getId();
	void setMatShininess(float);
	void setMatSpecular(float, float, float, float);
	void setMatDiffuse(float, float, float, float);
	void setMatAmbient(float, float, float, float);
	void setMatEmission(float, float, float, float);

	void applyMat();
};

#endif