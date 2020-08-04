//
// Created by frazor on 30/07/2020.
//

#ifndef SAND_ROGUE_MAIN_GAME_LOOP_H
#define SAND_ROGUE_MAIN_GAME_LOOP_H

#include "Source/Common.h"
#include "Source/Core/Game_Objects.h"
#include "Source/Sand_Maths/Matrix_Utils.h"
#include "Source/Graphical_User_Interface/User_Input.h"
#include "Source/GURPS/Sand_Combat.h"
#include "Source/GURPS/Sand_Damage.h"

void Main_Game_Loop(
    GLint shader,
    Dungeon_Level_Current* dungeon_level_current,
    Game_Model floor_model,
    SDL_Window* window
);

#endif //SAND_ROGUE_MAIN_GAME_LOOP_H
