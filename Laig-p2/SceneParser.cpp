#include "SceneParser.h"



map<string,Primitive*> mprimitivas;
map<string,Textures *> mtextura;
map<string, Transformation*> mtransformations; 
map<string, Material*> mmaterials;
map<string, Light*> mlight;
map<string, Component*> mcomponent;
map<string, View*> mview;

View * createView(TiXmlElement * viewchild){
    float flodo;
    if(viewchild ){
        View * ret;
        string id="";
        if(viewchild->ValueTStr()=="perspective" && (id=viewchild->Attribute("id"))!="" 
           && viewchild->QueryFloatAttribute("near",&flodo)==TIXML_SUCCESS
           && viewchild->QueryFloatAttribute("far",&flodo)==TIXML_SUCCESS
           && viewchild->QueryFloatAttribute("angle",&flodo)==TIXML_SUCCESS){
            float near,far,angle;
            viewchild->QueryFloatAttribute("near",&near);
            viewchild->QueryFloatAttribute("far",&far);
            viewchild->QueryFloatAttribute("angle",&angle);
            TiXmlElement * from=viewchild->FirstChildElement("from");
            TiXmlElement * to=viewchild->FirstChildElement("to");
            if(from && to){
                float xf,yf,zf,xo,yo,zo;
                from->QueryFloatAttribute("x",&xf);
                from->QueryFloatAttribute("y",&yf);
                from->QueryFloatAttribute("z",&zf);
                to->QueryFloatAttribute("x",&xo);
                to->QueryFloatAttribute("y",&yo);
                to->QueryFloatAttribute("z",&zo);
                
                ret= new Perspective(near,far, angle, xf, yf, zf, xo, yo, zo);
                cout<<"perspective element id: "<<id<<" near: "<<near<<" far "
                <<far<<" angle "<<angle<<endl;
                cout<<"from x:"<<xf<<" y "<<yf<<" z "<<zf<<endl;
                cout<<"to x:"<<xo<<" y "<<yo<<" z "<<zo<<endl;
            }
        }else
            if(viewchild->ValueTStr()=="ortho" && (id=viewchild->Attribute("id"))!="" 
               && viewchild->QueryFloatAttribute("near",&flodo)==TIXML_SUCCESS
               && viewchild->QueryFloatAttribute("far",&flodo)==TIXML_SUCCESS
               && viewchild->QueryFloatAttribute("left",&flodo)==TIXML_SUCCESS
               && viewchild->QueryFloatAttribute("right",&flodo)==TIXML_SUCCESS
               && viewchild->QueryFloatAttribute("top",&flodo)==TIXML_SUCCESS
               && viewchild->QueryFloatAttribute("bottom",&flodo)==TIXML_SUCCESS){
                float near,far,left,right,top,bottom;
                
                viewchild->QueryFloatAttribute("near",&near);
                viewchild->QueryFloatAttribute("far",&far);
                viewchild->QueryFloatAttribute("left",&left);
                viewchild->QueryFloatAttribute("right",&right);
                viewchild->QueryFloatAttribute("top",&top);
                viewchild->QueryFloatAttribute("bottom",&bottom);
                
                ret= new Ortho(near,far,left, right, top, bottom);
                cout<<"ortho element id: "<<id<<" near: "<<near<<" far "
                <<far<<" left "<<left<<" right "<<right<<" top "<<top
                <<" bottom "<<bottom<<endl;
            }
        
    }
    return NULL;
}


int loadviews(TiXmlElement* view){
	float flodo;
	string default1="";
	if (view->ValueTStr()=="views" && ((default1=view->Attribute("default"))!="")){
		cout<<"Root Views default:"<<default1<<endl;
		//criar class
		TiXmlElement *viewchild=view->FirstChildElement();
		
		do{
            View * ret=createView(viewchild);
            //TODO
            //Decidir o que fazer;
            if(ret!=NULL){
                mview[ret->getId()]=ret;
            }
            
		}while((viewchild=viewchild->NextSiblingElement()));
        
		//validação do numero de views
		return 0;
	}
	return -1;
}



Illumination* loadillumination(TiXmlElement* illu){
	float flodo;
    Illumination * ilu;
	bool doublesided,local;
    bool back=false,ambi=false;
	if (illu->ValueTStr()=="illumination" 
		&& illu->QueryBoolAttribute("doublesided",&doublesided)==TIXML_SUCCESS
		&& illu->QueryBoolAttribute("local",&local)==TIXML_SUCCESS){
		cout<<"Root illumination doublesided:"<<doublesided
        <<" local "<<local<<endl;
		//criar class
		TiXmlElement *illuchild=illu->FirstChildElement();
        ilu = new Illumination();
        ilu->setDSided(doublesided);
        ilu->setLocal(local);
		do{
			if(illuchild ){
				float r,g,b,a;
				if(illuchild->ValueTStr()=="ambient"
                   && illuchild->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
                   && illuchild->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
                   && illuchild->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
                   && illuchild->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                    
                    ilu->setAmbient(r, g, b, a);
                    ambi=true;
                    cout<<"ambient element r: "<<r<<" g: "<<g<<" b "
                    <<b<<" a "<<a<<endl;
                }
				
                
                if(illuchild->ValueTStr()=="background"
                   && illuchild->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
                   && illuchild->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
                   && illuchild->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
                   && illuchild->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                    
					ilu->setBackground(r, g, b, a);
                    back=true;
					cout<<"background element r: "<<r<<" g: "<<g<<" b "
                    <<b<<" a "<<a<<endl;
                }
                
			}
            
            
		}while((illuchild=illuchild->NextSiblingElement()));
        if(ilu && back){
            //validação do numero de illu tem que ter as 2.
            return ilu;
        }
        else{
            return NULL;
        }
	}
    return NULL;
}


Material* createMaterial(TiXmlElement * child){
    Material * mat=NULL;
    bool ambient=false,emission=false,diffuse=false,specular=false,shininess=false;
    string id="";
    if(child
       && child->ValueTStr()=="material"
       && (id=child->Attribute("id"))!=""){
        TiXmlElement * propriedades=child->FirstChildElement();
        mat=new Material(id);
        do{ 
            float r,g,b,a,value;
            if(propriedades->ValueTStr()=="ambient"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                mat->setMatAmbient(r, g,b,a);
                ambient=true;
                //add to class
                cout<<"ambient element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
            if(propriedades->ValueTStr()=="emission"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                
                mat->setMatEmission(r, g,b,a);
                emission=true;
                cout<<"emission element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
            if(propriedades->ValueTStr()=="diffuse"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                mat->setMatDiffuse(r, g,b,a);
                diffuse=true;
                //add to class
                cout<<"diffuse element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
            if(propriedades->ValueTStr()=="specular"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                mat->setMatSpecular(r, g,b,a);
                specular=true;
                cout<<"specular element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
            if(propriedades->ValueTStr()=="shininess"
               && propriedades->QueryFloatAttribute("value",&value)==TIXML_SUCCESS
               ){
                
                mat->setMatShininess(value);
                shininess=true;
                cout<<"shininess element value: "<<value<<endl;
                
            }
        }while((propriedades=propriedades->NextSiblingElement()));
        
    }
    
    return NULL;
}


vector<Material*> loadvectormaterials(TiXmlElement* mat){
	float flodo;
    vector<Material*> vect;
	if(mat->ValueTStr()=="materials"){
		cout<<"Materials root"<<endl;
		TiXmlElement * child=mat->FirstChildElement();
        string id="";
		do{
            if(child&&child->ValueTStr()=="material"&& (id=child->Attribute("id"))!=""){
                Material * mat=mmaterials[id];
            if(mat!=NULL)
                vect.push_back(mat);
            }
            
            
		}while((child=child->NextSiblingElement())!=NULL);
        
	}
    
    return vect;
}

int loadmaterials(TiXmlElement* mat){
	float flodo;
	if(mat->ValueTStr()=="materials"){
		cout<<"Materials root"<<endl;
		TiXmlElement * child=mat->FirstChildElement();
		do{
            Material * mat=createMaterial(child);
            if(mat!=NULL)
                mmaterials[mat->getId()]=mat;
        
            
		}while((child=child->NextSiblingElement())!=NULL);
        
	}
    
    return 0;
}


Light * createLight(TiXmlElement * child){
    Light* light=NULL;
    string id="";
    bool location=false,ambient=false,specular=false,diffuse=false,target=false;
    bool enabled = 0;
    float angle, exponent;
    if(child
       && child->ValueTStr()=="omni"
       && (id=child->Attribute("id"))!=""  && (child->QueryBoolAttribute("enabled",&enabled)==TIXML_SUCCESS)){
        cout<< "omni id: " << id << " enabled : " << enabled <<endl;
        TiXmlElement * propriedades=child->FirstChildElement();
        //declarar class
        light=new Omni(0);
        do{ 
            float r,g,b,a,value, x,y,z,w;
            if(propriedades->ValueTStr()=="location"
               && propriedades->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("z",&z)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("w",&w)==TIXML_SUCCESS){
                
                //add to class
                light->setLightLocation(x, y, z, w);
                location=true;
                cout<<"location x: "<<x<<" y: "<<y<<" z "
                <<z<<" w "<<w<<endl;
                
            }
            
            if(propriedades->ValueTStr()=="ambient"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                
                light->setLightAmbient(r, g, b, a);
                ambient=true;
                cout<<"ambient element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
            if(propriedades->ValueTStr()=="specular"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                
                //add to class
                specular=true;
                light->setLightSpecular(r,g,b,a);
                cout<<"specular element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
            if(propriedades->ValueTStr()=="diffuse"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                
                //add to class
                diffuse=true;
                light->setLightDiffuse(r,g,b,a);
                cout<<"diffuse element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
        }while((propriedades=propriedades->NextSiblingElement()));
        if(diffuse &&ambient&&ambient &&location){
            return light;
        }
        
    }
    if(child
       && child->ValueTStr()=="spot"
       && (id=child->Attribute("id"))!=""  && (child->QueryBoolAttribute("enabled",&enabled)==TIXML_SUCCESS) && (child->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
       && (child->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS)){
        cout<< "spot id: " << id << " enabled : " << enabled << " angle: " << angle << " exponent: " << exponent << endl;
        TiXmlElement * propriedades=child->FirstChildElement();
        //declarar class
        light=new Spot(0, angle);
        do{ 
            float r,g,b,a,value, x,y,z;
            if(propriedades->ValueTStr()=="location"
               && propriedades->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("z",&z)==TIXML_SUCCESS){
                
                light->setLightLocation(x, y, z, 0);
                location=true;
                cout<<"location x: "<<x<<" y: "<<y<<" z "
                <<z<<endl;
                
            }
            if(propriedades->ValueTStr()=="target"
               && propriedades->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("z",&z)==TIXML_SUCCESS){
                
                //add to class
                target=true;
                light->setSpotTarget(x, y, z);
                cout<<"target x: "<<x<<" y: "<<y<<" z "
                <<z<<endl;
                
            }
            
            if(propriedades->ValueTStr()=="ambient"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                
                //add to class
                light->setLightAmbient(r, g, b, a);
                ambient=true;
                cout<<"ambient element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
            if(propriedades->ValueTStr()=="specular"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                
                //add to class
                light->setLightSpecular(r, g, b, a);
                specular=true;
                cout<<"specular element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
            if(propriedades->ValueTStr()=="diffuse"
               && propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
               && propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
                
                //add to class
                light->setLightDiffuse(r, g, b, a);
                diffuse=true;
                cout<<"diffuse element r: "<<r<<" g: "<<g<<" b "
                <<b<<" a "<<a<<endl;
                
            }
        }while((propriedades=propriedades->NextSiblingElement()));
        if(diffuse &&ambient&&ambient &&location&&target){
            return light;
        }
    }
    
    
    return NULL;
    
}

int loadlights(TiXmlElement* lights){
	float flodo;
	if(lights->ValueTStr()=="lights"){
		cout<<"Lights root"<<endl;
		TiXmlElement * child=lights->FirstChildElement();
		do{
			Light * l=createLight(child);
            if(l!=NULL)
                mlight[l->getId()]=l;
            
		}while((child=child->NextSiblingElement())!=NULL);
        
    }
	return 0;
}

Textures * createTexture(TiXmlElement * child){
    string id, file;
    Textures* a;
    float length_s=0, length_t=0;
    if(child
       && child->ValueTStr()=="texture"
       && (id=child->Attribute("id"))!=""  && (file=child->Attribute("file"))!="" && (child->QueryFloatAttribute("length_s", (float*)&length_s)==TIXML_SUCCESS)
       && (child->QueryFloatAttribute("length_t",&length_t)==TIXML_SUCCESS)){
        
        a= (Textures*) new Textures(id, length_s, length_t, (char *)file.c_str(), 0);
        //a->setLengthS(length_s);
        //a->setLengthT(length_t);
        if(a!=NULL){
            mtextura[id]=a;
            cout<<"textura id: "<<id<<" added"<<endl;
        }
        cout<< "id: " << id << " file: " << file << " length_s: " << length_s << " length_t: " << length_t<<endl;
        return a;
    }
    return NULL;
    
}

int loadtextures(TiXmlElement* textures){
	
	if (textures->ValueTStr()=="textures"){
		cout<<"Textures root"<<endl;
		TiXmlElement * child=textures->FirstChildElement();
		do{
			Textures * a= createTexture(child);

            
        }while((child=child->NextSiblingElement())!=NULL);
	}
	return 0;
}

int loadscene(TiXmlElement* scene){
	string root;
	float axis_length;
	if(scene->ValueTStr()=="scene"){
		if((root=scene->Attribute("root"))!="" && scene->QueryFloatAttribute("axis_length",&axis_length)==TIXML_SUCCESS){
			cout << "scene root -" <<  root << " axis_length: " << axis_length << endl;
		}
		return axis_length;
	}
	return 0;
}



Transformation * createTransformation(TiXmlElement * child){
    string id;
    Transformation * trans=NULL;
    cout<<"create transform" << child->Value()<<endl;
    if(child && child->ValueTStr()=="transformation" ){
        if(child->Attribute("id")!=NULL){
            id=child->Attribute("id");
        }else{
            id="Lodo";
        }
        cout << "Transformation id: "<< id << endl;
        trans=new Transformation(id);
        TiXmlElement * subchild = child->FirstChildElement();
        do{
            float x, y, z, angle;
            string axis;
            if(subchild->ValueTStr()=="translate"
               && subchild->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("z",&z)==TIXML_SUCCESS){
                
                //add to class
                trans->translate(x, y, z);
                cout<<"translate: x:"<<x<<" y: "<<y<<" z "
                <<z<<endl;
                
            }
            
            if(subchild->ValueTStr()=="rotate"
               && (axis=subchild->Attribute("axis"))!=""
               && subchild->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS){
                int ax=0,ay=0,az=0;
                
                if(axis=="x" || axis=="X"){
                    ax=1;
                }
                if(axis=="y" || axis=="Y"){
                    ay=1;
                }
                if(axis=="z" || axis=="Z"){
                    az=1;
                }
                cout<<axis<<" ax: "<<ax<<" ay: "<<ay<<" az: "<<az<<endl;
                //add to class
                trans->rotate(angle, ax, ay, az);
                cout<<"rotate: axis:"<<axis<<" angle: "<<angle<<endl;
                
            }
            
            if(subchild->ValueTStr()=="scale"
               && subchild->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("z",&z)==TIXML_SUCCESS){
                
                //add to class
                trans->scale(x, y, z);
                cout<<"scale: x:"<<x<<" y: "<<y<<" z "
                <<z<<endl;
                
            }
            
        }while((subchild=subchild->NextSiblingElement())!=NULL);
        
        return trans;
    }else if(child
             && child->ValueTStr()=="transformationref"
             && child->Attribute("id")!=NULL){
        id=child->Attribute("id");
        cout<<"Responder a transformationref id: "<<id<<endl;
        if(mtransformations[id]!=NULL)
            return mtransformations[id];
        else
            cout<<"Erro a encontrar trans"<<endl;
        exit(-1);
    }
    
    return NULL;
}


int loadtransformations(TiXmlElement* transformations){
	if (transformations->ValueTStr()=="transformations"){
		cout<<"Transformations root"<<endl;
		TiXmlElement * child=transformations->FirstChildElement();
		//string id;
		do{
            Transformation * t=createTransformation(child);
            if(t!=NULL)
                mtransformations[t->getId()]=t;
            
		}while((child=child->NextSiblingElement())!=NULL);
	}
	return 0;
    
}


Primitive * createPrimitive(TiXmlElement * child){
    Primitive * prim;
    string id;
    if(child->ValueTStr()=="primitive" && child->Attribute("id")!=NULL){
        id=child->Attribute("id");
        cout << "id: " << id << endl;
        TiXmlElement* subchild = child->FirstChildElement();
        float x1, y1, x2, y2, z1, z2, x3, y3, z3, base, top, height, radius, inner, outer;
        int slices, stacks, loops;
        string id_mat,id_tex;
        TiXmlElement * saved=NULL;
        bool mat=false,tex=false,type=false;
        do{
            
            
            
            if(subchild->ValueTStr()=="material"
               && (id_mat=subchild->Attribute("id"))!=""){
                mat=true;
                //add to class
                cout<<"material: id:"<<id<<endl;
            }
            if(subchild->ValueTStr()=="texture"
               && (id_tex=subchild->Attribute("id"))!=""){
                tex=true;
                //add to class
                cout<<"texture: id:"<<id<<endl;
            }
            if(subchild->ValueTStr()=="rectangle" ||
               subchild->ValueTStr()=="triangle" ||
               subchild->ValueTStr()=="cylinder" ||
               subchild->ValueTStr()=="sphere"   ||
               subchild->ValueTStr()=="torus"  ){
                type=true;
                saved=subchild;
                
            }
            
            
        }while((subchild=subchild->NextSiblingElement())!=NULL && !(type&tex&mat));
        if(saved!=NULL && type==true){
            subchild=saved;
            
            if(subchild->ValueTStr()=="rectangle"
               && subchild->QueryFloatAttribute("x1",&x1)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("y1",&y1)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("x2",&x2)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("y2",&y2)==TIXML_SUCCESS){
                
                prim=new Rectangle(id,id_tex, id_mat, x1, y1,x2, y2);
                cout<<"rectangle: x1:"<<x1<<" y1: "<<y1<<" x2: "
                <<x2<< " y2: " << y2 <<endl;
                return prim;
                
            }
            if(subchild->ValueTStr()=="triangle"
               && subchild->QueryFloatAttribute("x1",&x1)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("y1",&y1)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("z1",&z1)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("x2",&x2)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("y2",&y2)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("z2",&z2)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("x3",&x3)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("y3",&y3)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("z3",&z3)==TIXML_SUCCESS){
                
                prim=new Triangle(id, id_tex, id_mat, x1, y1, z1, x2, y2, z2, x3, y3, z3);
                cout<<"rectangle: x1:"<<x1<<" y1: "<<y1<< " z1: "<<z1<<
                "x2: "<<x2<< " y2: " << y2 << " z2: " << z2 <<
                " x3: " << x3 << " y3: " << y3 << " z3: " << z3 <<endl;
                return prim;
            }
            
            if(subchild->ValueTStr()=="cylinder"
               && subchild->QueryFloatAttribute("base",&base)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("top",&top)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("height",&height)==TIXML_SUCCESS
               && subchild->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS
               && subchild->QueryIntAttribute("stacks",&stacks)==TIXML_SUCCESS){
                
                //add to class
                prim = new Cylinder(id, id_tex, id_mat, base, top, height, slices, stacks);
                cout<<"cylinder: base:"<<base<<" top: "<<top<<" height: "
                <<height<< " slices: " << slices << " stacks: " << stacks << endl;
                return prim;
                
            }
            if(subchild->ValueTStr()=="sphere"
               && subchild->QueryFloatAttribute("radius",&radius)==TIXML_SUCCESS
               && subchild->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS
               && subchild->QueryIntAttribute("stacks",&stacks)==TIXML_SUCCESS){
                
                //add to class
                prim=new Sphere(id, id_tex, id_mat, radius, slices, stacks);
                cout<<"Sphere: radius:"<<radius << " slices: " << slices << " stacks: " << stacks << endl;
                return prim;
                
            }
            
            if(subchild->ValueTStr()=="torus"
               && subchild->QueryFloatAttribute("inner",&inner)==TIXML_SUCCESS
               && subchild->QueryFloatAttribute("outer",&outer)==TIXML_SUCCESS
               && subchild->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS
               && subchild->QueryIntAttribute("loops",&loops)==TIXML_SUCCESS){
                
                //add to class
                prim=new Torus(id, id_tex, id_mat, inner, outer, slices, loops);
                cout<<"torus: inner:"<<inner << " outer: "<< outer<< " slices: " << slices << " loops: " << loops << endl;
                return prim;
            }
        
        
        }
        
        
        
    }
    else if(child && child->ValueTStr()=="primitiveref" && (id=child->Attribute("id"))!=""){
        return mprimitivas[id];
    }
    
    
    
    return NULL;
}


int loadprimitives(TiXmlElement* primitives){
	if(primitives->ValueTStr()=="primitives"){
		cout << "Primitives root" << endl;
		TiXmlElement* child = primitives->FirstChildElement();
		do{
			Primitive * p=createPrimitive(child);
            if(p!=NULL)
                mprimitivas[p->getId()]=p;
		}while((child=child->NextSiblingElement())!=NULL);
	}
	return 0;
}

Component* loadcomponent(TiXmlElement * component){
    string id;
    Textures * vtex=NULL;
    if(component->ValueTStr()=="component" && (id=component->Attribute("id"))!=""){
        cout<<"Component id: "<<id<<endl;
        TiXmlElement * transformation=component->FirstChildElement("transformation");
        TiXmlElement * materials=component->FirstChildElement("materials");
        TiXmlElement * texture=component->FirstChildElement("texture");
        TiXmlElement * children=component->FirstChildElement("children");
        if(transformation!=NULL&&materials!=NULL&&texture!=NULL&&children!=NULL){
            Transformation * trans=NULL;
            if(transformation->NoChildren()){
                trans=new Transformation("");
            }else
            if((transformation->FirstChildElement("transformationref"))!=NULL){
                //cout<<transformation->FirstChildElement()->Value()<<endl;
                trans=createTransformation(transformation->FirstChildElement("transformationref"));
                
            }else{
                //cout<<transformation->FirstChildElement()->Value()<<endl;
                trans=createTransformation(transformation);
            }
            string key="";
            vector<Material*> vmat;
            if(materials->Attribute("key")!=NULL){ 
                vmat=loadvectormaterials(materials);
                //falta atribuir tecla
            }else{
                vmat=loadvectormaterials(materials);
            }
            string id_tex;
            
            if(texture->Attribute("id")!=NULL){
                id_tex=texture->Attribute("id");
                if(mtextura[id_tex]!=NULL)
                    vtex=mtextura[id_tex];
                else
                    cout<<"Texture not found "<<id_tex<<endl;
            }
            
            TiXmlElement * childchild=children->FirstChildElement();
            vector<string> vcomp;
            vector<Primitive*> vprim;
            do{
                string id_c="";
                if(childchild && childchild->Attribute("id")!=NULL){
                    id_c=childchild->Attribute("id");
                    if(childchild->ValueTStr()=="componentref"){
                        cout<<"children cmpref id: "<<id_c<<endl;
                        vcomp.push_back(id_c);
                        /*Component * cmp=mcomponent[id_c];
                        if(cmp!=NULL){
                            cout<<"children comp id: "<<id_c<<endl;
                            vcomp.push_back(cmp);
                        }*/
                    }else if(childchild->ValueTStr()=="primitiveref"){
                        cout<<"children primref id: "<<id_c<<endl;
                        Primitive * cmp=mprimitivas[id_c];
                        if(cmp!=NULL){
                            cout<<"children primitiva id: "<<id_c<<endl;
                            vprim.push_back(cmp);
                        }
                    }
                
                }
            
            }while((childchild=childchild->NextSiblingElement())!=NULL);
            Component * newcmp=new Component(vcomp, vprim,vmat, vtex, trans);
            mcomponent[id]=newcmp;
            return newcmp;
        }
        
    }
    
    
    return NULL;
}


int loadcomponents(TiXmlElement * components){
    if(components->ValueTStr()=="components"){
        TiXmlElement * child=components->FirstChildElement();
        
        do{
            loadcomponent(child);
        }while((child=child->NextSiblingElement())!=NULL);
        
        for(map<string,Component*>::iterator it=mcomponent.begin();it!=mcomponent.end();it++){
            if((*it).second!=NULL){
                vector<string> v=(*it).second->getIDvector();
                vector<Component*> c;
                for(int i=0; i<v.size();i++){
                   Component* cp= mcomponent[v[i]];
                    if(cp!=NULL){
                        c.push_back(cp);
                    }
                }
                (*it).second->setComp(c);
            
            }
        }
        
    }
    
    return -1;
}

TiXmlElement* raiz=NULL;

int loaddsxfile(const string & filename){
	TiXmlDocument doc( filename.c_str() );
	bool lodo=doc.LoadFile();
	if(!lodo){
		cout<<filename<<" not found!!!"<<endl;
		return -1;
	}
    
	raiz=doc.FirstChildElement("dsx");
	if(raiz){
		TiXmlElement* scene=raiz->FirstChildElement("scene");
		TiXmlElement* component=raiz->FirstChildElement("components");
		TiXmlElement* views=raiz->FirstChildElement("views");
		TiXmlElement* illumination=raiz->FirstChildElement("illumination");
		TiXmlElement* lights=raiz->FirstChildElement("lights");
		TiXmlElement* textures=raiz->FirstChildElement("textures");
		TiXmlElement* materials=raiz->FirstChildElement("materials");
		TiXmlElement* transformations=raiz->FirstChildElement("transformations");
		TiXmlElement* primitives=raiz->FirstChildElement("primitives");
        string rootcomp="";
        if(scene->Attribute("root")){
            rootcomp=scene->Attribute("root");
        
        }else{
            return -1;
        }
		int length = loadscene(scene);
		loadviews(views);
		loadillumination(illumination);
		loadlights(lights);
		loadtextures(textures);
		loadmaterials(materials);
		
		loadtransformations(transformations);
		//loadcomponents(component);
		loadprimitives(primitives);
        loadcomponents(component);
        
        for(map<string,Primitive*>::iterator it=mprimitivas.begin();it!=mprimitivas.end();it++){
            if((*it).second!=NULL){
                (*it).second->setMat(mmaterials[(*it).second->getMat()]);
                (*it).second->setTex(mtextura[(*it).second->getTex()]);
            }
        }

        
        
        glNewList(1, GL_COMPILE);
        //(*mview.begin()).second->apply();
        for(map<string,Light*>::iterator it=mlight.begin();it!=mlight.end();it++){
            if((*it).second!=NULL)
                (*it).second->apply(true);
            
        }
        mcomponent[rootcomp]->apply();
        glEndList();
		return length;
	}

	return 0;
}