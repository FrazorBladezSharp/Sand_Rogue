//
// Created by frazor on 25/07/2020.
//

#ifndef SAND_ROGUE_MAP_H
#define SAND_ROGUE_MAP_H

#include "Source/Common.h"
#include "Source/Sand_Dice.h"


Dungeon_Level_Current* Map_Create_Dungeon_Level(
    Dungeon_Level_Current* dungeon_level_current
);

Point_3D Map_Random_Point_In_Room(
    u32 current_room
);

bool Map_Carve_Room(Dungeon_Level_Current *dungeon_level_current,
                    u32 x, u32 y, u32 x_axis, u32 z_axis);

void Map_Create_Corridor(
    Dungeon_Level_Current *dungeon_level_current,
    u32 room_count
);

void Map_Carve_Corridor_Horizontal(Dungeon_Level_Current* dungeon_level_current,
                                    Point_3D from, Point_3D to);

void Map_Carve_Corridor_Vertical(Dungeon_Level_Current* dungeon_level_current,
                                    Point_3D from, Point_3D to);

i32 Map_Number_Of_Rooms();

Dungeon_Level_Rooms* Map_Lookup_Room(i32 room_number);

#endif //SAND_ROGUE_MAP_H
