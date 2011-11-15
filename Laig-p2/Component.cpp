#include "Component.h"

Component::Component(vector<string> id_comp, vector<Primitive*> child_prim, vector<Material*> materials,Textures* texture, Transformation* transf){
	this->id_comp= id_comp;
	this->child_prim = child_prim;
	this->texture = texture;
	this->transf = transf;
    this->materials=materials;
}

vector<string> Component::getIDvector(){
    return this->id_comp;
}

void Component::setComp(vector<Component*> cmp){

    this->child_comp=cmp;
}


void Component::apply(){
       
        glPushMatrix();
        if(transf!=NULL){
    
            transf->apply();
        }
    
    for(vector<Material*>::iterator it= this->materials.begin(); it != this->materials.end(); ++it){
        (*it)->applyMat();
    }  

    if(this->texture!=NULL){
        this->texture->apply();}

    
        for(vector<Primitive*>::iterator it= child_prim.begin(); it != child_prim.end(); ++it){
            if(this->texture!=NULL)
                (*it)->render(texture);
        }
    
        for(vector<Component*>::iterator it= child_comp.begin(); it != child_comp.end(); ++it){
                (*it)->apply();
        }
        glPopMatrix();
}
