#ifndef LIGHTS_H_
#define LIGHTS_H_

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <gl/glut.h>
#endif
#ifdef __APPLE__
#include <GLUI/GLUI.h>
#else
#include <gl/glui.h>
#endif
#include <string>
#include <cmath>
using namespace std;

class Light{
	
	int light_number;
	
	float ambient[4];
	float specular[4];
	float diffuse[4];
    static int used;
    
    
protected:
    
    string id;
    bool enabled;
public:
	Light(int number);
	int getNumber();
	void setLightAmbient(float, float, float, float);
	void setLightSpecular(float, float, float, float);
	void setLightDiffuse(float, float, float, float);
	string getId();
    virtual void setSpotTarget(float x, float y, float z)=0;
    virtual void setLightLocation(float, float, float, float)=0;
	void setEnabled(bool enabled);
    int getLightX();
	bool is_enabled();
    virtual void apply()=0;
	virtual void apply(bool enabled)=0;
};

class Omni:public Light{
	float location[4];
public:
	Omni(int number);
	void setLightLocation(float, float, float, float);
    void setSpotTarget(float x, float y, float z){}
    void apply();
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
    void apply();
	void apply(bool enabled);
};

#endif