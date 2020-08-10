//
// Created by frazor on 30/07/2020.
//

#ifndef SAND_ROGUE_USER_INPUT_H
#define SAND_ROGUE_USER_INPUT_H

#include "Source/Common.h"
#include "Source/Sand_Maths/Matrix_Utils.h"

Current_Game_State User_Keyboard_Input(
    Current_Game_State current_game_state,
    Dungeon_Level_Current* dungeon_level_current
    //Position* monster_position
);

#endif //SAND_ROGUE_USER_INPUT_H
