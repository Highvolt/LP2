#ifndef VIEWS_H_
#define VIEWS_H_

#include <GL\glui.h>
#include <string>

using namespace std;

class View{
	string id;
	float near, far;

public:
	View();
    void setNear(float near);
    void setFar(float far);
    void virtual apply(float,float,float)=0;
};

class Perspective:public View{
	float angle, from_x, from_y, to_x, to_y, to_z;
public:
	Perspective();
	 void apply(float,float,float);
};

class Ortho:public View{
	float left, right, top, bottom;
public:
	Ortho();
	void apply(float,float,float);
};


#endif
