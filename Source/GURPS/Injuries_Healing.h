//
// Created by frazor on 14/08/2020.
//

#ifndef SAND_ROGUE_INJURIES_HEALING_H
#define SAND_ROGUE_INJURIES_HEALING_H

#include "Source/Common.h"
#include "Source/GURPS/Sand_Damage.h"

i32 Injuries_Healing_Update(
    bool is_resting,
    Current_Game_State* current_game_state
);

#endif //SAND_ROGUE_INJURIES_HEALING_H
