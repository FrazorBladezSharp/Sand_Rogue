//
// Created by frazor on 31/07/2020.
//

#ifndef SAND_ROGUE_SAND_COMBAT_H
#define SAND_ROGUE_SAND_COMBAT_H

#include "Source/Common.h"
#include "Source/Sand_Dice.h"
#include "Source/Core/Game_Objects.h"

i32 Sand_Attack_Roll(
    i32 attacker,
    i32 defender
);

bool Defence_Roll(i32 object_id);

#endif //SAND_ROGUE_SAND_COMBAT_H
