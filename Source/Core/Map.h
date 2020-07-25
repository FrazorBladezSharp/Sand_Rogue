//
// Created by frazor on 25/07/2020.
//

#ifndef SAND_ROGUE_MAP_H
#define SAND_ROGUE_MAP_H

#include "Source/Common.h"
#include "Source/Sand_Dice.h"



Dungeon_Level_Current* Map_Create_Dungeon_Level(Dungeon_Level_Current *dungeon_level_current);

Game_Component Map_Random_Point_In_Room(Game_Component position, u32 room);

bool Map_Carve_Room(Dungeon_Level_Current *dungeon_level_current,
                    u32 x, u32 y, u32 width, u32 height);

void Map_Carve_Corridor_Horizontal(vec2 from, vec2 to);

void Map_Carve_Corridor_Vertical(vec2 from, vec2 to);

#endif //SAND_ROGUE_MAP_H
