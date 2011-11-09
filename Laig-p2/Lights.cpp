#include "Lights.h"

Light::Light(int number){
	this->light_number = number;
}

void Light::setLightAmbient(float red, float green, float blue, float alpha) {
        this->ambient[0]=red;
		this->ambient[1]=green;
		this->ambient[2]=blue;
		this->ambient[3]=alpha;
        glLightfv(light_number, GL_AMBIENT, ambient);
}

void Light::setLightDiffuse(float red, float green, float blue, float alpha) {
		this->diffuse[0]=red;
		this->diffuse[1]=green;
		this->diffuse[2]=blue;
		this->diffuse[3]=alpha;
        glLightfv(light_number, GL_DIFFUSE, diffuse);
}

void Light::setLightSpecular(float red, float green, float blue, float alpha) {
		this->specular[0]=red;
		this->specular[1]=green;
		this->specular[2]=blue;
		this->specular[3]=alpha;
        glLightfv(light_number, GL_SPECULAR, specular);
}

int Light::getNumber(){
	return light_number;
}

void Light::setEnabled(bool enabled){
	this->enabled = enabled;
	if(enabled)
		glEnable(light_number);
	else
		glDisable(light_number);
}

bool Light::is_enabled(){
	return this->enabled;
}

Omni::Omni(int number):Light(number){}

void Omni::setLightLocation(float x, float y, float z, float w) {
		this->location[0]=x;
		this->location[1]=y;
		this->location[2]=z;
		this->location[3]=w;
		int num = this->getNumber();
        glLightfv(num, GL_POSITION, location);
}

void Omni::apply(bool enabled){
	if(enabled)
		glLightfv(this->getNumber(), GL_POSITION, location);
}

Spot::Spot(int number, float angle): Light(number){
	this->angle = 0;
	this->setLightLocation(0.0,0.0,0.0,0);
}

void Spot::setLightLocation(float x, float y, float z, float w) {
		this->location[0]=x;
		this->location[1]=y;
		this->location[2]=z;
		this->location[3]=w;
		int num = this->getNumber();
        glLightfv(num, GL_POSITION, location);
}

void Spot::setSpotAngle(float angle){
	this->angle=angle;
}

void Spot::setSpotExponent(float exponent){
	this->exponent = exponent;
}

void Spot::setSpotTarget(float x, float y, float z){
	this->direction[0] = x - this->location[0];
    this->direction[1] = y - this->location[1];
    this->direction[2] = z - this->location[2];
    double d0_pow = direction[0]*direction[0];
	double d1_pow = direction[1]*direction[1];
	double d2_pow = direction[2]*direction[2];
    double norma = sqrt(d0_pow+d1_pow+d2_pow);
    this->direction[0] /= norma;
	this->direction[1] /= norma;
	this->direction[2] /= norma;
	int num = this->getNumber();
    glLightfv(num, GL_SPOT_DIRECTION, direction);
}

void Spot::apply(bool enabled){
	if(enabled){
		glLightfv(this->getNumber(), GL_POSITION, location);
        glLightfv(this->getNumber(), GL_SPOT_DIRECTION, direction);
	}
}

