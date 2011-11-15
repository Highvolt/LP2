#include "Texture.h"
#include <iostream>

int Textures::pos_tex=1;

Textures::Textures(string id, float ls, float lt, char* file, int tex_type)
{
	if(tex_type == 0){
        cout<<"A contruir com ls: "<<ls<<" lt "<<lt<<endl;
		this->id_texture = id;
		this->file = file;
		this->length_s = ls;
		this->length_t = lt;
		RGBpixmap * pixmap = new RGBpixmap();
		this->id_num = pos_tex++;
        pixmap->readBMPFile(file);
		pixmap->setTexture(this->id_num);
	}else if(tex_type == 1){
		this->inherits = true;
	}else if(tex_type == 2){
		this->has_none = true;
	}
}

string Textures::getId(){
	return id_texture;
}

int Textures::getIdNum(){
	return id_num;
}

void Textures::setLengthS(float lenght_s){
	this->length_s = lenght_s;
}

void Textures::setLengthT(float lenght_t){
	this->length_t = lenght_t;
}

float Textures::getLengthS(){
	return length_s;
}
    
float Textures::getLengthT(){
	return length_t;
}

void Textures::apply(){
        if(has_none){
            glBindTexture(GL_TEXTURE_2D,0);
            glDisable(GL_TEXTURE_2D);
        }
        else
            glEnable(GL_TEXTURE_2D);
        if(!inherits)
		 glBindTexture(GL_TEXTURE_2D,this->id_num);
}
