//
// Created by frazor on 08/08/2020.
//

#ifndef SAND_ROGUE_MONSTERS_H

#include "Source/Sand_Dice.h"
#include "Source/OpenGL/Load_Model_3D.h"

// NOTE : model_component = Game_Model model_component[MAX_ENTITIES]  object = Game_Object object[MAX_ENTITIES]

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

void Monsters_Data_Initialize();

char Monsters_Add_To_Room(
    i8 dungeon_level
);

char Monsters_Add_Wandering(
    i8 dungeon_level
);

const char* Monsters_Name(i32 monster_id);
Health_Status Monsters_Health_Status(i32 monster_id);
u8 Monsters_Treasure(i32 monster_id);
u32 Monsters_AI_To_Use(i32 monster_id);
i32 Monsters_Will(i32 monster_id);
float Monsters_Base_Speed(i32 monster_id);
i32 Monsters_Unit_Xp(i32 monster_id);
i32 Monsters_Hit_Points_Max(i32 monster_id);
i32 Monsters_Hit_Points_Current(i32 monster_id);
i32 Monsters_Damage_Resistance(i32 monster_id);
i32 Monsters_Dodge(i32 monster_id);
u8 Monsters_Attack_Skill(i32 monster_id);
Damage_Type Monsters_Special_Attack(i32 monster_id);
Damage_Type Monsters_Damage_Type(i32 monster_id);
u8 Monsters_Damage_Melee(i32 monster_id);
u8 Monsters_Damage_Ranged(i32 monster_id);
i32 Monsters_Shock(i32 monster_id);
i32 Monster_Health(i32 monster_id);
i32 Monster_Attack_Target(i32 target_id);


#define SAND_ROGUE_MONSTERS_H

#endif //SAND_ROGUE_MONSTERS_H
