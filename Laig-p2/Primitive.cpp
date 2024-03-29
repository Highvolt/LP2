//
//  Primitive.cpp
//  Laig-p2
//
//  Created by Pedro Borges on 02/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Primitive.h"
#include <cmath>

Primitive::Primitive(string id,string texture,string material){
	this->id=id;
    if(texture.compare("inherit")!=0 && texture.compare("none")!=0){
        this->texture=texture;
    }else{
        tex=NULL;
    }
	this->material=material;

}

string Primitive::getId(){
	return id;
}

Torus::Torus(string id, string texture, string material, float inner, float outer,int slices,int stacks):Primitive(id,texture,material){
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->stacks = stacks;
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
}

int Torus::render(Textures* tx){
    if(this->tex!=NULL && this->texture.compare("inherit")!=0)
        this->tex->apply();
    glPushMatrix();
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    glutSolidTorus(inner, outer, slices, stacks);
	glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    
	glPopMatrix();
	return 0;
}

Cylinder::Cylinder(string id, string texture, string material,float base,float top,float height,int slices,int stacks):Primitive(id,texture,material){
	
    this->base = base;
	this->height = height;
	this->top = top;
	this->slices = slices;
	this->stacks = stacks;
	glQ = gluNewQuadric();
    gluQuadricDrawStyle(glQ, GLU_FILL);             
    gluQuadricNormals(glQ, GLU_SMOOTH);             
    gluQuadricOrientation(glQ, GLU_OUTSIDE);
    gluQuadricTexture(glQ, GL_TRUE);
}

int Cylinder::render(Textures* tx){
    glEnable(GL_NORMALIZE);
    if(tex!=NULL){
        tx=tex;
    }
    if(tx!=NULL)
    tx->apply();
    //glQ = gluNewQuadric();
	/*glPushMatrix();
	glRotated(180,0,1,0);
    gluDisk(glQ,0,base,slices,stacks);
    
	glPopMatrix();
    glPushMatrix(); 
	gluCylinder(glQ,base,top,height,slices,stacks);
	glTranslated(0,0,height);
    gluDisk(glQ,0,top,slices,stacks);
	glPopMatrix();*/
   
    glPushMatrix();         
    glRotated(180,0,1,0);
    gluDisk(glQ,0,base,slices,stacks);
    glPopMatrix();
    glPushMatrix(); 
    gluCylinder(glQ,base,top,height,slices,stacks);
    glTranslated(0,0,height);
    gluDisk(glQ,0,top,slices,stacks);
    glPopMatrix();
	return 0;
}


Triangle::Triangle(string id, string texture, string material,
	float x1,float y1,float z1,float x2,float y2,float z2, float x3, float y3,float z3):Primitive(id,texture,material){
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
int Triangle::render(Textures* tx){
    glEnable(GL_NORMALIZE);
    if(tex!=NULL){
        tx=tex;
    }
    if(tx!=NULL)
        tx->apply();
	float acN= sqrt( (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) + (z3-z1)*(z3-z1));
    float abN= sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
	float ab[3],ac[3];
    ab[0]=(x2-x1)/abN;
    ab[1]=(y2-y1)/abN;
    ab[2]=(z2-z1)/abN;
    ac[0]=(x3-x1)/acN;
    ac[1]=(y3-y1)/acN;
    ac[2]=(z3-z1)/acN;
        
    float cosAlfa =abs(ab[0]*ac[0]+ab[1]*ac[1]+ab[2]*ac[2]);
    float AD = abN*cosAlfa;
    float AE = abN*sin(acos(cosAlfa));


    glColor3d(1.0, 1.0, 1.0);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    
    glVertex3f(x1, y1, z1);
    if(tx!=NULL)
    glTexCoord2f(acN/tx->getLengthS(), 0.0);
    glVertex3f(x2, y2, z2); 
    if(tx!=NULL)
    glTexCoord2f(AD/tx->getLengthS(),AE/tx->getLengthT());
    glVertex3f(x3, y3, z3);
    if(tx!=NULL)
    glTexCoord2f(0.0, 0.0);
    

    glEnd();
	glPopMatrix();

		return 0;

}

Rectangle::Rectangle(string id, string texture, string material,float x1,float y1,float x2, float y2):Primitive(id,texture,material){
    this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

int Rectangle::render(Textures* tx){
	glEnable(GL_NORMALIZE);
    bool has_texture=false;
    if(tex!=NULL){
        tx=tex;
    }
    if(tx!=NULL)
	tx->apply();
    
    glPushMatrix();
    //VERIFICA SE TEM TEXTURA
    //CARREGAR MATERIAL
    if(tx!=NULL){
            glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tx->getIdNum());
    }
    float ls,lt,xrep,yrep;
	if(tx!=NULL){
    ls=tx->getLengthS();
    lt=tx->getLengthT();
	xrep = (x2-x1)  /ls;
    yrep = (y2-y1)  /lt;}
    glColor3d(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glNormal3d(0, 0, 1);
	if(tx!=NULL)glTexCoord2f(0.0, 0.0); 
    glVertex3f(x1, y1, 0);
	if(tx!=NULL)glTexCoord2f(xrep, 0.0);
    glVertex3f(x2, y1, 0);
	if(tx!=NULL)glTexCoord2f(xrep, yrep);
    glVertex3f(x2, y2, 0);
	if(tx!=NULL)glTexCoord2f(0.0, yrep); 
    glVertex3f(x1, y2, 0);
    glEnd();
	glPopMatrix();
    if(tx!=NULL)
        glDisable(GL_TEXTURE_2D);
		return 0;
	
}

Sphere::Sphere(string id, string texture, string material, float radius,int slices,int stacks):Primitive(id,texture,material){
    this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
	glQ = gluNewQuadric();
    gluQuadricDrawStyle(glQ, GLU_FILL);             
    gluQuadricNormals(glQ, GLU_SMOOTH);             
    gluQuadricOrientation(glQ, GLU_OUTSIDE);
    gluQuadricTexture(glQ, GL_TRUE);}

int Sphere::render(Textures* tx){
    if(tex!=NULL && texture.compare("inherit")!=0){
        tx=tex;
    }
    if(tx!=NULL)
        tx->apply();
    glEnable(GL_NORMALIZE);
	glPushMatrix();
	gluSphere(glQ, radius, slices, stacks);
	glPopMatrix();
    return 0;
}