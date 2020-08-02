//
// Created by frazor on 29/07/2020.
//

#ifndef SAND_ROGUE_GAME_OBJECTS_H
#define SAND_ROGUE_GAME_OBJECTS_H

#include "Source/Common.h"
#include "Source/Core/Sand_Vector.h"
#include "Source/OpenGL/Load_Model_3D.h"
#include "Source/Core/Map.h"

void Object_Initialize();

void Object_Create(
    i32 ascii_character,
    vec4 color,
    u32 starting_room,
    const char* file_path
);

void* Object_Lookup_Component(u32 object_id, u8 component);

void Object_Add_VAO(GLint data);
void Object_Add_VBO(GLint data);

void Object_Cleanup();

#endif //SAND_ROGUE_GAME_OBJECTS_H
