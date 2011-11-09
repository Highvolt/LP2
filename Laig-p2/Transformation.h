#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include <GL/glui.h>
#include <string>
using namespace std;


class Transformation{
	string id;
	float transf_matrix[4][4];

public:
	Transformation(string id);
	void rotate(float, float, float, float);
	void translate(float, float, float);
	void scale(float, float, float);

	float* getTransformationMatrix();
};

#endif
