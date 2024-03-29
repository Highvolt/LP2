#include "Illumination.h"

Illumination::Illumination(){}

void Illumination::setAmbient(float red, float green, float blue, float alpha){
	this->ambient[0] = red;
	this->ambient[1] = green;
	this->ambient[2] = blue;
	this->ambient[3] = alpha;
}

float* Illumination::getAmbient(){
	return this->ambient;
}

void Illumination::setBackground(float red, float green, float blue, float alpha){
	this->background[0] = red;
	this->background[1] = green;
	this->background[2] = blue;
	this->background[3] = alpha;
}

float* Illumination::getBackground(){
	return this->background;
}

void Illumination::setLocal(bool local){
	this->local = local;
}

bool Illumination::getLocal(){
	return this->local;
}

void Illumination::setDSided(bool doublesided){
	this->doublesided = doublesided;
}

bool Illumination::getDSided(){
	return this->doublesided;
}

void Illumination::apply(){
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
        glClearColor(background[0],background[1],background[2],background[3]);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,doublesided);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
}
