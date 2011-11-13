#include "Views.h"

View::View(float near, float far){
	this->setNear(near);
	this->setFar(far);
}

void View::setNear(float near){
	this->near=near;
}

void View::setFar(float far){
	this->far=far;
}

Perspective::Perspective(float near,float far, float angle, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z):View(near, far){
        this->angle=angle;
        this->from_x=from_x;
        this->from_y=from_y;
        this->from_z=from_z;
        this->to_x=to_x;
        this->to_y=to_y;
        this->to_z=to_z;  
}

void Perspective::apply(){
        gluPerspective(angle, xy_aspect, near,far);
        if(to_x==from_x && to_z==from_z)
                gluLookAt(from_x,from_y,from_z,to_x,to_y,to_z,1,0,0);
        else
                gluLookAt(from_x,from_y,from_z,to_x,to_y,to_z,0,1,0);
}


Ortho::Ortho(float near, float far, float left, float right, float top, float bottom):View(near,far){
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

void Ortho::apply(){
        glOrtho(left,  right,  bottom,  top,  near,  far);
}
