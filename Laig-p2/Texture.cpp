#include "Texture.h"


Texture::Texture(int id, float ls, float lt, char* file, int tex_type)
{
	if(tex_type == 0){
		this->id_texture = id;
		this->file = file;
		this->length_s = ls;
		this->length_t = lt;
		RGBpixmap * pixmap = new RGBpixmap();
        pixmap->readBMPFile(file);
		pixmap->setTexture(id_texture);
	}else if(tex_type == 1){
		this->inherits = true;
	}else if(tex_type == 2){
		this->has_none = true;
	}
}

void Texture::setLengthS(float lenght_s){
	this->length_s = lenght_s;
}

void Texture::setLengthT(float lenght_t){
	this->length_t = lenght_t;
}

float Texture::getLengthS(){
	return length_s;
}
    
float Texture::getLengthT(){
	return length_t;
}

void Texture::apply(){
        if(has_none){
            glBindTexture(GL_TEXTURE_2D,0);
            glDisable(GL_TEXTURE_2D);
        }
        else
            glEnable(GL_TEXTURE_2D);
        if(!inherits)
            glBindTexture(GL_TEXTURE_2D,id_texture);
}
