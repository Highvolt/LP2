#include "Component.h"
#include <iostream>
Component::Component(vector<string> id_comp, vector<Primitive*> child_prim, vector<Material*> materials,Textures* texture, Transformation* transf){
	this->id_comp= id_comp;
	this->child_prim = child_prim;
	this->texture = texture;
	this->transf = transf;
    this->materials=materials;
    if(materials.size()>0)
        activo=materials[0];
    else
        activo=NULL;
    lastpos=0;
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
    
    /*for(vector<Material*>::iterator it= this->materials.begin(); it != this->materials.end(); ++it){
        (*it)->applyMat();
    } */
    



    
        for(vector<Primitive*>::iterator it= child_prim.begin(); it != child_prim.end(); ++it){
            if(activo!=NULL && activo->getId().compare("inherit")!=0){
                // cout<<this->id<<" material activo: "<<this->activo->getId()<<endl;
                activo->applyMat();
            }
             if(this->texture!=NULL && texture->getId().compare("none")!=0 && texture->getId().compare("inherit")!=0){
                this->texture->apply();}

                (*it)->render(texture);
            
        
        }
    
        for(vector<Component*>::iterator it= child_comp.begin(); it != child_comp.end(); ++it){

            if(activo!=NULL && activo->getId().compare("inherit")!=0){
                // cout<<this->id<<" material activo: "<<this->activo->getId()<<endl;
                activo->applyMat();
            }
            if(this->texture!=NULL && texture->getId().compare("none")!=0 && texture->getId().compare("inherit")!=0){
                this->texture->apply();}    

            (*it)->apply();
        }
        glPopMatrix();
}
