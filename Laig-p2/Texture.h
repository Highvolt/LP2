#ifndef TEXTURE_H_
#define TEXTURE_H_


#ifdef __APPLE__
#include <GLUI/GLUI.h>
#else
#include <gl/glui.h>
#endif
#include "RGBpixmap.h"
#include <string>

using namespace std;


class Texture{
	string id_texture;
	float length_s;
    float length_t;
	char* file;

public:
	bool has_none, inherits;
	Texture(string id, float ls, float lt, const char* file, int tex_type);
	void setLengthS(float lenght_s);
    void setLengthT(float lenght_t);
    float getLengthS();
    float getLengthT();
	void apply();
};

#endif