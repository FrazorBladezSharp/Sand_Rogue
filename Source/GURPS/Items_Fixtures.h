//
// Created by frazor on 10/08/2020.
//

#ifndef SAND_ROGUE_ITEMS_FIXTURES_H
#define SAND_ROGUE_ITEMS_FIXTURES_H

#include "Source/Sand_Dice.h"
#include "Source/OpenGL/Load_Model_3D.h"
#include "Source/Core/Dungeon_Level.h"

// NOTE : model_component = Game_Model model_component[MAX_ENTITIES]  object = Game_Object object[MAX_ENTITIES]

void Items_Initialize_Models(
    Vector *vao_storage,
    Vector *vbo_storage,
    Game_Model *model_component,
    Game_Object *object
);

void Items_Load_Model(
    i32 object_id,
    vec4 color,
    const char* file_path,
    Vector *vao_storage,
    Vector *vbo_storage,
    Game_Model *model_component,
    Game_Object *object
);

Dungeon_Level_Current* Items_Add_Fixtures_To_Level();

void Items_Add_to_Room(i32 number_of_dungeon_rooms);


#endif //SAND_ROGUE_ITEMS_FIXTURES_H
