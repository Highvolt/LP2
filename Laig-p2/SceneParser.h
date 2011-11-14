//
//  SceneParser.cpp
//  Laig-p2
//
//  Created by Pedro Borges on 02/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <iostream>
#include <map>
#include "Primitive.h"
#include "Lights.h"
#include "Material.h"
#include "Texture.h"
#include "Views.h"
#include "Illumination.h"
#include "Texture.h"
#include "Transformation.h"
#include "Component.h"
#include <string>
//#include <cstdlib>
#include "../tinyxml.h"
using namespace std;
 



int loaddsxfile(const string & filename);