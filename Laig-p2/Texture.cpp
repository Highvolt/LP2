#include "Texture.h"


int Texture::pos_tex=0;

Texture::Texture(string id, float ls, float lt, char* file, int tex_type)
{
	if(tex_type == 0){
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

string Texture::getId(){
	return id_texture;
}

int Texture::getIdNum(){
	return id_num;
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
		 glBindTexture(GL_TEXTURE_2D,this->id_num);
}
