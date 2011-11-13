#include "SceneParser.h"

int loadviews(TiXmlElement* view){
	float flodo;
	string default="";
	if (view->ValueTStr()=="views" && ((default=view->Attribute("default"))!="")){
		cout<<"Root Views default:"<<default<<endl;
		//criar class
		TiXmlElement *viewchild=view->FirstChildElement();
		
		do{
		if(viewchild ){
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

						//criar class;
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

						//criar class;
						cout<<"ortho element id: "<<id<<" near: "<<near<<" far "
							<<far<<" left "<<left<<" right "<<right<<" top "<<top
							<<" bottom "<<bottom<<endl;
			}
			
		}

		}while((viewchild=viewchild->NextSiblingElement()));

		//valida��o do numero de views
		return 0;
	}
	return -1;
}


int loadillumination(TiXmlElement* illu){
	float flodo;
	bool doublesided,local;
	if (illu->ValueTStr()=="illumination" 
		&& illu->QueryBoolAttribute("doublesided",&doublesided)==TIXML_SUCCESS
		&& illu->QueryBoolAttribute("local",&local)==TIXML_SUCCESS){
		cout<<"Root illumination doublesided:"<<doublesided
			<<" local "<<local<<endl;
		//criar class
		TiXmlElement *illuchild=illu->FirstChildElement();

		do{
			if(illuchild ){
				float r,g,b,a;
				if(illuchild->ValueTStr()=="ambient"
					&& illuchild->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
					&& illuchild->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
					&& illuchild->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
					&& illuchild->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

							//criar class;
							cout<<"ambient element r: "<<r<<" g: "<<g<<" b "
								<<b<<" a "<<a<<endl;
						}
				

			if(illuchild->ValueTStr()=="background"
				&& illuchild->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
				&& illuchild->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
				&& illuchild->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
				&& illuchild->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

					//criar class;
					cout<<"background element r: "<<r<<" g: "<<g<<" b "
						<<b<<" a "<<a<<endl;
			}
		
			}
		

		}while((illuchild=illuchild->NextSiblingElement()));

		//valida��o do numero de illu tem que ter as 2.
	}
return 0;
}

int loadmaterials(TiXmlElement* mat){
	float flodo;
	if(mat->ValueTStr()=="materials"){
		cout<<"Materials root"<<endl;
		TiXmlElement * child=mat->FirstChildElement();
		do{
			string id="";
			if(child
				&& child->ValueTStr()=="material"
				&& (id=child->Attribute("id"))!=""){
					TiXmlElement * propriedades=child->FirstChildElement();
					//declarar class
					do{ 
						float r,g,b,a,value;
						if(propriedades->ValueTStr()=="ambient"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
								
								//add to class
								cout<<"ambient element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;
							
						}
						if(propriedades->ValueTStr()=="emission"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

								//add to class
								cout<<"emission element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;

						}
						if(propriedades->ValueTStr()=="diffuse"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

								//add to class
								cout<<"diffuse element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;

						}
						if(propriedades->ValueTStr()=="specular"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

								//add to class
								cout<<"specular element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;

						}
						if(propriedades->ValueTStr()=="shininess"
							&& propriedades->QueryFloatAttribute("value",&value)==TIXML_SUCCESS
							){

								//add to class
								cout<<"shininess element value: "<<value<<endl;

						}
					}while((propriedades=propriedades->NextSiblingElement()));

			}
		}while((child=child->NextSiblingElement())!=NULL);

	}

return 0;
}

int loadlights(TiXmlElement* lights){
	float flodo;
	if(lights->ValueTStr()=="lights"){
		cout<<"Lights root"<<endl;
		TiXmlElement * child=lights->FirstChildElement();
		do{
			string id="";
			bool enabled = 0;
			float angle, exponent;
			if(child
				&& child->ValueTStr()=="omni"
				&& (id=child->Attribute("id"))!=""  && (child->QueryBoolAttribute("enabled",&enabled)==TIXML_SUCCESS)){
					cout<< "omni id: " << id << " enabled : " << enabled <<endl;
					TiXmlElement * propriedades=child->FirstChildElement();
					//declarar class
					do{ 
						float r,g,b,a,value, x,y,z,w;
						if(propriedades->ValueTStr()=="location"
							&& propriedades->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("z",&z)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("w",&w)==TIXML_SUCCESS){
								
								//add to class
								cout<<"location x: "<<x<<" y: "<<y<<" z "
									<<z<<" w "<<w<<endl;
							
						}

						if(propriedades->ValueTStr()=="ambient"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
								
								//add to class
								cout<<"ambient element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;
							
						}
						if(propriedades->ValueTStr()=="specular"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

								//add to class
								cout<<"specular element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;

						}
						if(propriedades->ValueTStr()=="diffuse"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

								//add to class
								cout<<"diffuse element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;

						}
					}while((propriedades=propriedades->NextSiblingElement()));}
			if(child
				&& child->ValueTStr()=="spot"
				&& (id=child->Attribute("id"))!=""  && (child->QueryBoolAttribute("enabled",&enabled)==TIXML_SUCCESS) && (child->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				&& (child->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS)){
					cout<< "spot id: " << id << " enabled : " << enabled << " angle: " << angle << " exponent: " << exponent << endl;
					TiXmlElement * propriedades=child->FirstChildElement();
					//declarar class
					do{ 
						float r,g,b,a,value, x,y,z;
						if(propriedades->ValueTStr()=="location"
							&& propriedades->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("z",&z)==TIXML_SUCCESS){
								
								//add to class
								cout<<"location x: "<<x<<" y: "<<y<<" z "
									<<z<<endl;
							
						}
						if(propriedades->ValueTStr()=="target"
							&& propriedades->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("z",&z)==TIXML_SUCCESS){
								
								//add to class
								cout<<"target x: "<<x<<" y: "<<y<<" z "
									<<z<<endl;
							
						}

						if(propriedades->ValueTStr()=="ambient"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){
								
								//add to class
								cout<<"ambient element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;
							
						}
						if(propriedades->ValueTStr()=="specular"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

								//add to class
								cout<<"specular element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;

						}
						if(propriedades->ValueTStr()=="diffuse"
							&& propriedades->QueryFloatAttribute("r",&r)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("g",&g)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("b",&b)==TIXML_SUCCESS
							&& propriedades->QueryFloatAttribute("a",&a)==TIXML_SUCCESS){

								//add to class
								cout<<"diffuse element r: "<<r<<" g: "<<g<<" b "
									<<b<<" a "<<a<<endl;

						}
					}while((propriedades=propriedades->NextSiblingElement()));}
		}while((child=child->NextSiblingElement())!=NULL);

}
	return 0;
}

int loadtextures(TiXmlElement* textures){
	
	if (textures->ValueTStr()=="textures"){
		cout<<"Textures root"<<endl;
		TiXmlElement * child=textures->FirstChildElement();
		do{
			string id, file;
			float length_s, length_t;
			if(child
				&& child->ValueTStr()=="texture"
				&& (id=child->Attribute("id"))!=""  && (file=child->Attribute("file"))!="" && (child->QueryFloatAttribute("length_s",&length_s)==TIXML_SUCCESS)
				&& (child->QueryFloatAttribute("length_t",&length_t)==TIXML_SUCCESS)){
					cout<< "id: " << id << " file: " << file << " length_s: " << length_s << " length_t: " << length_t<<endl;
			}
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
	}
	return 0;
}

int loadtransformations(TiXmlElement* transformations){
	if (transformations->ValueTStr()=="transformations"){
		cout<<"Transformations root"<<endl;
		TiXmlElement * child=transformations->FirstChildElement();
		string id;
		do{

		if(child && child->ValueTStr()=="transformation" && (id=child->Attribute("id"))!=""){
			cout << "Transformation id: "<< id << endl;
			TiXmlElement * subchild = child->FirstChildElement();
			do{
				float x, y, z, angle;
				string axis;
				if(subchild->ValueTStr()=="translate"
				&& subchild->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
				&& subchild->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
				&& subchild->QueryFloatAttribute("z",&z)==TIXML_SUCCESS){

					//add to class
					cout<<"translate: x:"<<x<<" y: "<<y<<" z "
						<<z<<endl;

				}

				if(subchild->ValueTStr()=="rotate"
				&& (axis=subchild->Attribute("axis"))!=""
				&& subchild->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS){

					//add to class
					cout<<"rotate: axis:"<<axis<<" angle: "<<angle<<endl;

				}

				if(subchild->ValueTStr()=="scale"
				&& subchild->QueryFloatAttribute("x",&x)==TIXML_SUCCESS
				&& subchild->QueryFloatAttribute("y",&y)==TIXML_SUCCESS
				&& subchild->QueryFloatAttribute("z",&z)==TIXML_SUCCESS){

					//add to class
					cout<<"scale: x:"<<x<<" y: "<<y<<" z "
						<<z<<endl;

				}

				}while((subchild=subchild->NextSiblingElement())!=NULL);
		}
		}while((child=child->NextSiblingElement())!=NULL);
	}
	return 0;
}

int loadprimitives(TiXmlElement* primitives){
	if(primitives->ValueTStr()=="primitives"){
		cout << "Primitives root" << endl;
		TiXmlElement* child = primitives->FirstChildElement();
		do{
			string id;
			if(child->ValueTStr()=="primitive" && (id=child->Attribute("id"))!=""){
				cout << "id: " << id << endl;
				TiXmlElement* subchild = child->FirstChildElement();
				do{
					string id;
					float x1, y1, x2, y2, z1, z2, x3, y3, z3, base, top, height, radius, inner, outer;
					int slices, stacks, loops;

					if(subchild->ValueTStr()=="material"
						&& (id=subchild->Attribute("id"))!=""){

						//add to class
						cout<<"material: id:"<<id<<endl;
					}
					if(subchild->ValueTStr()=="texture"
						&& (id=subchild->Attribute("id"))!=""){

						//add to class
						cout<<"texture: id:"<<id<<endl;
					}
					if(subchild->ValueTStr()=="rectangle"
					&& subchild->QueryFloatAttribute("x1",&x1)==TIXML_SUCCESS
					&& subchild->QueryFloatAttribute("y1",&y1)==TIXML_SUCCESS
					&& subchild->QueryFloatAttribute("x2",&x2)==TIXML_SUCCESS
					&& subchild->QueryFloatAttribute("y2",&y2)==TIXML_SUCCESS){

						//add to class
						cout<<"rectangle: x1:"<<x1<<" y1: "<<y1<<" x2: "
							<<x2<< " y2: " << y2 <<endl;

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

						//add to class
						cout<<"rectangle: x1:"<<x1<<" y1: "<<y1<< " z1: "<<z1<<
							"x2: "<<x2<< " y2: " << y2 << " z2: " << z2 <<
							" x3: " << x3 << " y3: " << y3 << " z3: " << z3 <<endl;
					}

					if(subchild->ValueTStr()=="cylinder"
					&& subchild->QueryFloatAttribute("base",&base)==TIXML_SUCCESS
					&& subchild->QueryFloatAttribute("top",&top)==TIXML_SUCCESS
					&& subchild->QueryFloatAttribute("height",&height)==TIXML_SUCCESS
					&& subchild->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS
					&& subchild->QueryIntAttribute("stacks",&stacks)==TIXML_SUCCESS){

						//add to class
						cout<<"cylinder: base:"<<base<<" top: "<<top<<" height: "
							<<height<< " slices: " << slices << " stacks: " << stacks << endl;

					}
					if(subchild->ValueTStr()=="sphere"
					&& subchild->QueryFloatAttribute("radius",&radius)==TIXML_SUCCESS
					&& subchild->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS
					&& subchild->QueryIntAttribute("stacks",&stacks)==TIXML_SUCCESS){

						//add to class
						cout<<"cylinder: radius:"<<radius << " slices: " << slices << " stacks: " << stacks << endl;

					}

					if(subchild->ValueTStr()=="torus"
					&& subchild->QueryFloatAttribute("inner",&inner)==TIXML_SUCCESS
					&& subchild->QueryFloatAttribute("outer",&outer)==TIXML_SUCCESS
					&& subchild->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS
					&& subchild->QueryIntAttribute("loops",&loops)==TIXML_SUCCESS){

						//add to class
						cout<<"torus: inner:"<<inner << " outer: "<< outer<< " slices: " << slices << " loops: " << loops << endl;

					}


				}while((subchild=subchild->NextSiblingElement())!=NULL);
			}
		}while((child=child->NextSiblingElement())!=NULL);
	}
	return 0;
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

		loadscene(scene);
		loadviews(views);
		loadillumination(illumination);
		loadlights(lights);
		loadtextures(textures);
		loadmaterials(materials);
		
		loadtransformations(transformations);
		//loadcomponents(component);
		loadprimitives(primitives);
	}
	return 0;
}