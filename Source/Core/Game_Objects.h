//
// Created by frazor on 29/07/2020.
//

#ifndef SAND_ROGUE_GAME_OBJECTS_H
#define SAND_ROGUE_GAME_OBJECTS_H

#include "Source/Common.h"
#include "Source/Core/Sand_Vector.h"
#include "Source/OpenGL/Load_Model_3D.h"

static Position g_position_component[MAX_ENTITIES];
static Game_Model g_model_component[MAX_ENTITIES];

void Object_Initialize();

Game_Object Object_Create(const char* file_path);

void Object_Add_VAO(GLint data);
void Object_Add_VBO(GLint data);

void Object_Cleanup();

#endif //SAND_ROGUE_GAME_OBJECTS_H
