#include "Component.h"

Component::Component(vector<Component*> child_comp, vector<Primitive*> child_prim, Texture* texture, Transformation* transf){
	this->child_comp = child_comp;
	this->child_prim = child_prim;
	this->texture = texture;
	this->transf = transf;
}

void Component::apply(){
       
        glPushMatrix();
        transf->apply();
        
        for(vector<Primitive*>::iterator it= child_prim.begin(); it != child_prim.end(); ++it){
                (*it)->render();
        }
        

        for(vector<Component*>::iterator it= child_comp.begin(); it != child_comp.end(); ++it){
                (*it)->apply();
        }
        glPopMatrix();
}
