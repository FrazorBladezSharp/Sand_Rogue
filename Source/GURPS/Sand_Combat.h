//
// Created by frazor on 31/07/2020.
//

#ifndef SAND_ROGUE_SAND_COMBAT_H
#define SAND_ROGUE_SAND_COMBAT_H

#include "Source/Common.h"
#include "Source/Sand_Dice.h"
#include "Source/Core/Game_Objects.h"
#include "Source/GURPS/Sand_Damage.h"



//typedef enum {
//
//    DAMAGE_SMALL_PIERCING = 0,
//    DAMAGE_PIERCING,
//    DAMAGE_LARGE_PIERCING,
//    DAMAGE_IMPALING,
//    DAMAGE_CUTTING,
//    DAMAGE_CRUSHING,
//
//    DAMAGE_TYPE_COUNT               // keep a count on how many Damage Types we have
//
//} Damage_Type;

i32 Sand_Attack_Roll(
    i32 attacker,
    i32 object_id
);

bool Defence_Roll();

#endif //SAND_ROGUE_SAND_COMBAT_H
