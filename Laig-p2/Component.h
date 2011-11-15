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

#include <vector>
#include "Primitive.h"
#include "Material.h"
#include "Transformation.h"
#include "Texture.h"

class Component{
    vector<string> id_comp;
	vector<Component*> child_comp;
	vector<Primitive*> child_prim;
	vector<Material*> materials;
	Textures* texture;
	Transformation* transf;
	char key;
public:
	Component(vector<string> id_comp, vector<Primitive*> child_prim, vector<Material*> materials,Textures* texture, Transformation* transf);
	void apply();
    void setComp(vector<Component*> cmp);
    vector<string> getIDvector();

};

#endif