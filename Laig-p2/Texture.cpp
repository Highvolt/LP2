#include "Texture.h"


Texture::Texture(void)
{
	this->length_s = 1.0;
	this->length_t = 1.0;
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