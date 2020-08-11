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

Position* Dungeon_Place_Player(
    Position* position
);

Dungeon_Level_Current* Dungeon_level();

void Dungeon_Level_Cleanup();

#endif //SAND_ROGUE_DUNGEON_LEVEL_H
