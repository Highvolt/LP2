#ifndef LIGHTS_H_
#define LIGHTS_H_


#ifdef __APPLE__
#include <GLUI/GLUI.h>
#else
#include <gl/glui.h>
#endif
#include <string>
#include <cmath>
using namespace std;

class Light{
	string id;
	int light_number;
	bool enabled;
	float ambient[4];
	float specular[4];
	float diffuse[4];
public:
	Light(int number);
	int getNumber();
	void setLightAmbient(float, float, float, float);
	void setLightSpecular(float, float, float, float);
	void setLightDiffuse(float, float, float, float);
	void setEnabled(bool enabled);
	bool is_enabled();
	void virtual apply(bool enabled)=0;
};

class Omni:public Light{
	float location[4];
public:
	Omni(int number);
	void setLightLocation(float, float, float, float);
	void apply(bool enabled);
};

class Spot:public Light{
	float angle;
	float exponent;
	float location[4];
	float direction[3];
public:
	Spot(int number, float angle);
	void setSpotAngle(float);
	void setSpotExponent(float);
	void setSpotTarget(float x, float y, float z);
	void setLightLocation(float, float, float, float);
	void apply(bool enabled);
};

#endif