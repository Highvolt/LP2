//
//  Primitive.h
//  Laig-p2
//
//  Created by Pedro Borges on 02/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Laig_p2_Primitive_h
#define Laig_p2_Primitive_h

#include <string>

class Primitive {
    string id, texture,material;

public:
    Primitive();
    virtual int render();
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
    int render();
};

class Cylinder: public Primitive {
    float base,top,height;
    int slices,stacks;

public:
    Cylinder(string id, string texture, string material,float base,float top,float height,int slices,int stacks);
    int render();
};

class Triangle: public Primitive {
    float x1,y1,z1,x2,y2,z2,x3,y3,z3;

public:
    Triangle(string id, string texture, string material,float x1,float y1,float z1,float x2,float y2,float z2, float x3, float y3,float z3);
    int render();
};

class Rectangle: public Primitive {
    float x1,y1,x2,y2;

public:
    Rectangle(string id, string texture, string material,float x1,float y1,float x2, float y2);
};

#endif
