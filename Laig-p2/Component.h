#ifndef Laig_p2_Component_h
#define Laig_p2_Component_h

#include <string>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <gl/glut.h>
#endif
#ifdef __APPLE__
#include <GLUI/GLUI.h>
#else
#include <gl/glui.h>
#endif
using namespace std;
#include <iostream>
#include <vector>
#include "Primitive.h"
#include "Material.h"
#include "Transformation.h"
#include "Texture.h"

class Component{
    string id;
    vector<string> id_comp;
	vector<Component*> child_comp;
	vector<Primitive*> child_prim;
	vector<Material*> materials;
    Material * activo;
    int lastpos;
	Textures* texture;
	Transformation* transf;
	char key;
public:
	Component(vector<string> id_comp, vector<Primitive*> child_prim, vector<Material*> materials,Textures* texture, Transformation* transf);
	void apply();
    void setComp(vector<Component*> cmp);
    vector<string> getIDvector();
    void setKey(char c){
        this->key=c;
    }
    void receivekey(char pressed){
       // cout<<pressed<<" guardada "<<key<<endl;
        if(pressed==key && materials.size()>0){
        if(lastpos<(materials.size()-1)){
            lastpos++;
        }else{
            lastpos=0;
        }
            cout<<"tamanho vector: "<<materials.size()<<" pos: "<<lastpos<<endl;
        //lastpos=(lastpos+1)%materials.size();
            activo=materials[lastpos];
        }
    }
    void setId(string i){
        id=i;
    }

};

#endif