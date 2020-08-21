//
// Created by frazor on 31/07/2020.
//

#ifndef SAND_ROGUE_SAND_COMBAT_H
#define SAND_ROGUE_SAND_COMBAT_H

#include "Source/Sand_Dice.h"
#include "Source/Core/Game_Objects.h"
#include "Source/Core/Dungeon_Level.h"
#include "Source/GURPS/Sand_Damage.h"


void Sand_Combat_Update(i32 monster_id);

i32 Sand_Combat_Target_Search(i32 actor, Attack_Target direction);

i32 Sand_Combat_Melee_Resolution(
    i32 attacker_id,
    i32 defender_id
);

i32 Sand_Combat_Ranged_Resolution(
    i32 attacker_id
);

bool Defence_Roll(Monster_Stats* defender);

#endif //SAND_ROGUE_SAND_COMBAT_H
