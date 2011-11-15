#include "Lights.h"


int Light::used=0;


int Light::getLightX()
{
    switch(light_number){
        case 0:
            return GL_LIGHT0;
            break;
        case 1:
            return GL_LIGHT1;
            break;
        case 2:
            return GL_LIGHT2;
            break;
        case 3:
            return GL_LIGHT3;
            break;
        case 4:
            return GL_LIGHT4;
            break;
        case 5:
            return GL_LIGHT5;
            break;
        case 6:
            return GL_LIGHT6;
            break;
        case 7:
            return GL_LIGHT7;
            break;
    }
}



Light::Light(int number){
	this->light_number = used++;
}

string Light::getId(){
	return id;
}

void Light::setLightAmbient(float red, float green, float blue, float alpha) {
        this->ambient[0]=red;
		this->ambient[1]=green;
		this->ambient[2]=blue;
		this->ambient[3]=alpha;
        glLightfv(getLightX(), GL_AMBIENT, ambient);
}

void Light::setLightDiffuse(float red, float green, float blue, float alpha) {
		this->diffuse[0]=red;
		this->diffuse[1]=green;
		this->diffuse[2]=blue;
		this->diffuse[3]=alpha;
        glLightfv(getLightX(), GL_DIFFUSE, diffuse);
}

void Light::setLightSpecular(float red, float green, float blue, float alpha) {
		this->specular[0]=red;
		this->specular[1]=green;
		this->specular[2]=blue;
		this->specular[3]=alpha;
        glLightfv(getLightX(), GL_SPECULAR, specular);
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
        glLightfv(getLightX(), GL_POSITION, location);
}

void Omni::apply(bool enabled){
	if(enabled)
		glLightfv(getLightX(), GL_POSITION, location);
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
        glLightfv(getLightX(), GL_POSITION, location);
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
    glLightfv(getLightX(), GL_SPOT_DIRECTION, direction);
}

void Spot::apply(bool enabled){
	if(enabled){
		glLightfv(getLightX(), GL_POSITION, location);
        glLightfv(getLightX(), GL_SPOT_DIRECTION, direction);
	}
}

