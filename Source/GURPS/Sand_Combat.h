//
// Created by frazor on 31/07/2020.
//

#ifndef SAND_ROGUE_SAND_COMBAT_H
#define SAND_ROGUE_SAND_COMBAT_H

#include "Source/Common.h"
#include "Source/Sand_Dice.h"
#include "Source/Core/Game_Objects.h"
#include "Source/GURPS/Sand_Damage.h"


void Sand_Combat_Update(i32 monster_id);

i32 Sand_Combat_Resolution(
    i32 attacker_id,
    i32 defender_id
);

bool Defence_Roll(Monster_Stats* defender);

#endif //SAND_ROGUE_SAND_COMBAT_H
