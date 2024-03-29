//
//  Primitive.h
//  Laig-p2
//
//  Created by Pedro Borges on 02/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Laig_p2_Primitive_h
#define Laig_p2_Primitive_h

#include "Texture.h"
#include "Material.h"
#include <string>
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
using namespace std;

class Primitive {
protected:
    string id, texture,material;
    Textures * tex;
    Material * mat;

public:
    Primitive(string id,string texture,string material);
	string getId();
    virtual int render(Textures*)=0;
    string getTex(){
        return texture;
    }
    string getMat(){
        return material;
    }
    void setTex(Textures * tex){
        if(tex==NULL){
            this->tex=NULL;
        }else
        if(tex->getId().compare("inherit")!=0 && tex->getId().compare("none")!=0){
            this->tex=tex;
        }else{
            this->tex=NULL;
        }
    }
    void setMat(Material * mat){
        this->mat=mat;
    }
};
/*
class Circle: public Primitive {
  <#instance variables#>

public:
  <#member functions#>
};*/

class Torus: public Primitive {
    float inner, outer;
    int slices,stacks;

public:
    Torus(string id, string texture, string material, float inner, float outer,int slices,int stacks);
    int render(Textures*);
};

class Cylinder: public Primitive {
	GLUquadric* glQ;
    float base,top,height;
    int slices,stacks;

public:
    Cylinder(string id, string texture, string material,float base,float top,float height,int slices,int stacks);
    int render(Textures*);
};

class Triangle: public Primitive {
    float x1,y1,z1,x2,y2,z2,x3,y3,z3;

public:
    Triangle(string id, string texture, string material,float x1,float y1,float z1,float x2,float y2,float z2, float x3, float y3,float z3);
    int render(Textures*);
};

class Rectangle: public Primitive {
    float x1,y1,x2,y2;

public:
    Rectangle(string id, string texture, string material,float x1,float y1,float x2, float y2);
	int render(Textures*);
};

class Sphere: public Primitive {
	GLUquadric *glQ;
	float radius;
	int slices, stacks;

public:
	Sphere(string id, string texture, string material, float radius, int slices, int stacks);
	int render(Textures*);
};

#endif