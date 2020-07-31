//
// Created by frazor on 30/07/2020.
//

#ifndef SAND_ROGUE_USER_INPUT_H
#define SAND_ROGUE_USER_INPUT_H

#include "Source/Common.h"
#include "Source/Sand_Maths/Matrix_Utils.h"

Current_Game_State User_Input(
    Current_Game_State current_game_state,
    i32 mouseX,
    i32 mouseY,
    Dungeon_Level_Current* dungeon_level_current
);

#endif //SAND_ROGUE_USER_INPUT_H