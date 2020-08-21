//
// Created by frazor on 19/08/2020.
//

#ifndef SAND_ROGUE_MONSTER_AI_H
#define SAND_ROGUE_MONSTER_AI_H

#include "Source/Core/Dungeon_Level.h"

void Monster_AI_Dijkstra_Map(
    i32 target_x,
    i32 target_z
);

void Monster_AI_Register(
    Position* monster_position
);

bool Monster_AI_Mean(
    Position* monster_position
);

#endif //SAND_ROGUE_MONSTER_AI_H
