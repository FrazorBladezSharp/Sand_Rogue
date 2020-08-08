//
// Created by frazor on 08/08/2020.
//

#ifndef SAND_ROGUE_MONSTERS_H

#include "Source/Common.h"
#include "Source/Sand_Dice.h"
#include "Source/OpenGL/Load_Model_3D.h"

// model_component = Game_Model model_component[MAX_ENTITIES]  object = Game_Object object[MAX_ENTITIES]

void Monsters_Initialize_Models(
    Vector *vao_storage,
    Vector *vbo_storage,
    Game_Model *model_component,
    Game_Object *object
);

void Monsters_Load_Monster_Model(
    i32 object_id,
    vec4 color,
    const char* file_path,
    Vector *vao_storage,
    Vector *vbo_storage,
    Game_Model *model_component,
    Game_Object *object
);

void Monsters_For_New_Level(
    i8 current_dungeon_level
);

char Monsters_Add_Wandering(
    i8 dungeon_level
);

#define SAND_ROGUE_MONSTERS_H

#endif //SAND_ROGUE_MONSTERS_H
