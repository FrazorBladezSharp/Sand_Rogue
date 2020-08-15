//
// Created by frazor on 14/08/2020.
//

#include "Injuries_Healing.h"

i32 Injuries_Healing_Update(
    bool is_resting,
    Current_Game_State* current_game_state){

/*
   ///////////////////////// Natural Recovery ///////////////////////////////

    Rest lets you recover lost HP, unless the
    damage is of a type that specifically does
    not heal naturally (for an example, see
    Disease, p. 32). At the end of each day of rest
    and decent food, make a HT roll. On a success,
    you recover 1 HP. The GM may give a
    penalty if conditions are bad, or a bonus if
        conditions are very good.
*/

// this only applies if the player rests for a number of turns (10)
if(is_resting){

    current_game_state->number_of_rests++;
}

if(current_game_state->number_of_rests >= 10){

    Monster_Stats* player_stats = Object_Lookup_Component(
        64,
        COMP_MONSTER_STATS
    );
    // make a  health roll
    Health_Status temp = Damage_Health_Roll(
        player_stats->health,
        0,
        HEALTH_STATUS_RESTED
    );
    // players health + 1 if rest period is complete
    if(temp == HEALTH_STATUS_FULL_REST){

        if(player_stats->hit_points_current < player_stats->hit_points_max) {

            player_stats->hit_points_current += 1;
        }
    }
}

/////////////////////////////////////////////////////////////////////////
    //First Aid
    // Fatigue
    // Disease

    // Flame - see special attack

    // Heat

    // Poison - see special Attacks
    // Suffocation - see special Attacks


}
