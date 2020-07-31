//
// Created by frazor on 30/07/2020.
//

#ifndef SAND_ROGUE_MAIN_GAME_LOOP_H
#define SAND_ROGUE_MAIN_GAME_LOOP_H

#include "Source/Common.h"
#include "Source/Sand_Maths/Matrix_Utils.h"
#include "Source/Graphical_User_Interface/User_Input.h"
#include "Source/GURPS/Sand_Combat.h"

void Main_Game_Loop(
    GLint shader,
    Position* player_position,
    Position* monster_position,
    Dungeon_Level_Current* dungeon_level_current,
    Game_Model floor_model,
    Game_Model* player_model,
    Game_Model* monster_model,
    SDL_Window* window
);

#endif //SAND_ROGUE_MAIN_GAME_LOOP_H
