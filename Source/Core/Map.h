//
// Created by frazor on 25/07/2020.
//

#ifndef SAND_ROGUE_MAP_H
#define SAND_ROGUE_MAP_H

#include "Source/Common.h"
#include "Source/Sand_Dice.h"


Dungeon_Level_Current* Map_Create_Dungeon_Level(
    Dungeon_Level_Current* dungeon_level_current,
    Position* player_position
);

Point_3D Map_Random_Point_In_Room(
    Point_3D room_location,
    u8 room_width,
    u8 room_height);

bool Map_Carve_Room(Dungeon_Level_Current *dungeon_level_current,
                    u32 x, u32 y, u32 width, u32 height);

void Map_Create_Corridor(
    Dungeon_Level_Current *dungeon_level_current,
    Point_3D room_location,
    u8 room_width,
    u8 room_height,
    Point_3D old_room_location,
    u8 old_room_width,
    u8 old_room_height
);

void Map_Carve_Corridor_Horizontal(Dungeon_Level_Current* dungeon_level_current,
                                    Point_3D from, Point_3D to);

void Map_Carve_Corridor_Vertical(Dungeon_Level_Current* dungeon_level_current,
                                    Point_3D from, Point_3D to);

#endif //SAND_ROGUE_MAP_H
