//
// Created by frazor on 29/07/2020.
//

#ifndef SAND_ROGUE_GAME_OBJECTS_H
#define SAND_ROGUE_GAME_OBJECTS_H

#include "Source/Common.h"
#include "Source/Core/Sand_Vector.h"
#include "Source/OpenGL/Load_Model_3D.h"
#include "Source/Core/Map.h"
#include "Source/GURPS/Monsters.h"
#include "Source/GURPS/Items_Fixtures.h"

void Object_Initialize();

i32 Object_Create(
    i32 index,
    i32 ascii_character
);

void Object_Add_Position(
    i32 object_id,
    u32 room
);


/*
void Object_Add_Model(
    i32 object_id,
    vec4 color,
    const char* file_path
);
*/
void Object_Add_Primary_Characteristics(
    i32 object_id
);

void Object_Add_Secondary_Characteristics(
    i32 object_id
);

void Object_Add_Combat_Stats(
    i32 object_id
);

void Object_Add_Monster_Stats(
    i32 object_id
);

void* Object_Lookup_Component(
    i32 object_id,
    i32 component
);

void Object_Add_VAO(
    GLint data
);

void Object_Add_VBO(
    GLint data
);

void Object_Cleanup();

///////////////////////////// Items & Equipment /////////////////////////

void Game_Items_Initialize();

#endif //SAND_ROGUE_GAME_OBJECTS_H
