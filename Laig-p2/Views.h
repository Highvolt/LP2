#ifndef VIEWS_H_
#define VIEWS_H_

#include <GL\glui.h>
#include <string>

using namespace std;
extern float xy_aspect;

class View{
protected:
	string id;
	float near, far;

public:
	View(float near, float far);
    void setNear(float near);
    void setFar(float far);
    void virtual apply(float,float,float)=0;
};

class Perspective:public View{
	float angle, from_x, from_y, from_z, to_x, to_y, to_z;
public:
	 Perspective(float near,float far, float angle, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z);
     void apply();
};

class Ortho:public View{
	float left, right, top, bottom;
public:
	Ortho(float near, float far, float left, float right, float top, float bottom);
	void apply();
};


#endif
