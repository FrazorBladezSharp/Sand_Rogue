//
// Created by frazor on 04/08/2020.
//

#ifndef SAND_ROGUE_SAND_DAMAGE_H
#define SAND_ROGUE_SAND_DAMAGE_H

#include "Source/Core/Game_Objects.h"
#include "Source/Sand_Dice.h"

void Damage_Melee(
    Action opponents_action,
    i32 object_id,
    i32 damage
);

Health_Status Damage_Health_Roll(
    i32 health,
    i32 modifier,
    Health_Status type
);

#endif //SAND_ROGUE_SAND_DAMAGE_H
