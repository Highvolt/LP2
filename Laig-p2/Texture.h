#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glui.h>
#include "RGBpixmap.h"



class Texture{
	int id_texture;
	float length_s;
    float length_t;

public:
	Texture(void);
	void setLengthS(float lenght_s);
    void setLengthT(float lenght_t);
    float getLengthS();
    float getLengthT();
};

#endif