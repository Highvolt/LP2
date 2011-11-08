//
//  Primitive.cpp
//  Laig-p2
//
//  Created by Pedro Borges on 02/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Primitive.h"


Torus::Torus(string id, string texture, string material, float inner, float outer,int slices,int stacks){
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->stacks = stacks;
}

int Torus::render(){
	glutSolidTorus(inner, outer, slices, stacks);
}

Cylinder::Cylinder(string id, string texture, string material,float base,float top,float height,int slices,int stacks){
	this->base = base;
	this->height = height;
	this->top = top;
	this->slices = slices;
	this->stacks = stacks;
}

int Cylinder::render(){
	gluCylinder(glQ,base,top,height,slices,stacks);
}


Triangle::Triangle(string id, string texture, string material,
	float x1,float y1,float z1,float x2,float y2,float z2, float x3, float y3,float z3){
		this->x1 = x1;
		this->y1 = y1;
		this->z1 = z1;
		this->x2 = x2;
		this->y2 = y2;
		this->z2 = z2;
		this->x3 = x3;
		this->y3 = y3;
		this->z3 = z3;
}
int Triangle::render(){

	//Carregar textura e material

	glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    //glTexCoord2f(0,0);
    glVertex3f(x1,y1,z1);
    //glTexCoord2f();
    glVertex3f(x2,y2,z2);
    //glTexCoord2f();
    glVertex3f(x3,y3,z3);
    glEnd();


}

Rectangle::Rectangle(string id, string texture, string material,float x1,float y1,float x2, float y2){
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

int Rectangle::render(){
	bool has_texture=false;

    //VERIFICA SE TEM TEXTURA
    //CARREGAR MATERIAL
    if(has_texture){
            glEnable(GL_TEXTURE_2D);
           // glBindTexture(GL_TEXTURE_2D, /*id da textura*/);
    }
    glBegin(GL_POLYGON);
    glNormal3d(0, 0, 1);
    if(has_texture)
		glTexCoord2f(0.0, 0.0); 
    glVertex3f(x1, y1, 0);
    if(has_texture)
		glTexCoord2f(1.0, 0.0); 
    glVertex3f(x2, y1, 0);
    if(has_texture)
		glTexCoord2f(1.0, 1.0); 
    glVertex3f(x2, y2, 0);
    if(has_texture)
		glTexCoord2f(0.0, 1.0); 
    glVertex3f(x1, y2, 0);
    glEnd();

    if(has_texture)
        glDisable(GL_TEXTURE_2D);

}

Sphere::Sphere(string id, string texture, string material, float radius,int slices,int stacks){
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

int Sphere::render(){
	gluSphere(glQ, radius, slices, stacks);
}