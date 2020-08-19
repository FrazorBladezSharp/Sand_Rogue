//
// Created by frazor on 08/08/2020.
//

#ifndef SAND_ROGUE_DUNGEON_LEVEL_H
#define SAND_ROGUE_DUNGEON_LEVEL_H

#include "Source/Common.h"
#include "Map.h"

void Dungeon_Level_Initialize();

void Dungeon_Level_New(
    i8 dungeon_level
);

void Dungeon_Level_Add_Items_Fixtures(
    i32 fixture_id,
    i32 x,
    i32 z
);

void Dungeon_Place_Doors();

void Dungeon_Place_Stairs();

Position* Dungeon_Place_Items(
    i32 item_id,
    i32 room,
    Position* position
);

Position* Dungeon_Place_Player(
    Position* position
);

Position* Dungeon_Place_Monster(
    u32 current_room,
    Position* position
);

Dungeon_Level_Current* Dungeon_level();

void Dungeon_Level_Cleanup();

#endif //SAND_ROGUE_DUNGEON_LEVEL_H
