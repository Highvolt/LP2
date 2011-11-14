#include "Transformation.h"

Transformation::Transformation(string id){
	this->id = id;
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, &transf_matrix[0][0]);
	glPopMatrix();
}

string Transformation::getId(){
	return id;
}

void Transformation::rotate(float angle, float x, float y, float z){
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(&transf_matrix[0][0]);
	glRotatef(angle,x,y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX, &transf_matrix[0][0]);
	glPopMatrix();
}

void Transformation::scale(float x, float y, float z){
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(&transf_matrix[0][0]);
	glScalef(x,y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX, &transf_matrix[0][0]);
	glPopMatrix();
}

void Transformation::translate(float x, float y, float z){
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(&transf_matrix[0][0]);
	glTranslatef(x,y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX, &transf_matrix[0][0]);
	glPopMatrix();
}

float* Transformation::getTransformationMatrix(){
	return &transf_matrix[0][0];
}

void Transformation::apply(){
	 glMultMatrixf(&transf_matrix[0][0]);
}