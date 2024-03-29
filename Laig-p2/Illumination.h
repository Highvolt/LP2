#ifndef ILLUMINATION_H_
#define ILLUMINATION_H_

#ifdef __APPLE__
#include <GLUI/GLUI.h>
#else
#include <gl/glui.h>
#endif
using namespace std;

class Illumination{
	bool local;
	bool doublesided;
	float ambient[4];
	float background[4];
public:
	Illumination();
	void setAmbient(float, float, float, float);
	float* getAmbient();
	void setBackground(float, float, float ,float);
	float* getBackground();
	void setLocal(bool local);
	bool getLocal();
	void setDSided(bool doublesided);
	bool getDSided();
	void apply();
};

#endif