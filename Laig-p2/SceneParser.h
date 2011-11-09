//
//  SceneParser.cpp
//  Laig-p2
//
//  Created by Pedro Borges on 02/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <map>
#include "Primitive.h"
#include <string>
#include <cstdlib>
#include "../tinyxml.h"
using namespace std;
 


/*

map<string,Primitive*> primitivas;
map<string,int> textura;
map<string, float*> transformations; 
*/
int loaddsxfile(const string & filename);