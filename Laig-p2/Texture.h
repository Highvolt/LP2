#ifndef TEXTURE_H_
#define TEXTURE_H_


#ifdef __APPLE__
#include <GLUI/GLUI.h>
#else
#include <gl/glui.h>
#endif
#include "RGBpixmap.h"



class Texture{
	int id_texture;
	float length_s;
    float length_t;
	char* file;

public:
	bool has_none, inherits;
	Texture(int id, float ls, float lt, char* file, int tex_type);
	void setLengthS(float lenght_s);
    void setLengthT(float lenght_t);
    float getLengthS();
    float getLengthT();
	void apply();
};

#endif