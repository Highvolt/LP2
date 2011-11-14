#include "Material.h"

Material::Material(string id){
	this->id = id;
}

string Material::getId(){
	return id;
}

void Material::setMatShininess(float value){
	this->mat_shininess[0] = value;
}

void Material::setMatAmbient(float red, float green, float blue, float alpha){
	this->mat_ambient[0] = red;
	this->mat_ambient[1] = green;
	this->mat_ambient[2] = blue;
	this->mat_ambient[3] = alpha;
}

void Material::setMatDiffuse(float red, float green, float blue, float alpha){
	this->mat_diffuse[0] = red;
	this->mat_diffuse[1] = green;
	this->mat_diffuse[2] = blue;
	this->mat_diffuse[3] = alpha;
}

void Material::setMatSpecular(float red, float green, float blue, float alpha){
	this->mat_specular[0] = red;
	this->mat_specular[1] = green;
	this->mat_specular[2] = blue;
	this->mat_specular[3] = alpha;
}

void Material::setMatEmission(float red, float green, float blue, float alpha){
	this->mat_emission[0] = red;
	this->mat_emission[1] = green;
	this->mat_emission[2] = blue;
	this->mat_emission[3] = alpha;
}

void Material::applyMat(){
	glMaterialfv(GL_FRONT,GL_SHININESS,&mat_shininess[0]);
	glMaterialfv(GL_FRONT,GL_EMISSION,&mat_emission[0]);
	glMaterialfv(GL_FRONT,GL_SPECULAR,&mat_specular[0]);
	glMaterialfv(GL_FRONT,GL_AMBIENT,&mat_ambient[0]);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,&mat_diffuse[0]);
}