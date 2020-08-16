//
// Created by frazor on 31/07/2020.
//

#include "Sand_Combat.h"

/*
Melee Attacks
When you take a maneuver that lets you
make a melee attack, you must specify who
you are attacking, and with what weapon.
*/
/* (Frazor) we can place an enum in common.h
 *
You can make a melee attack using any
ready melee weapon (including a natural
weapon such as a kick, bite, or punch).
You can use some weapons in more than
one way; e.g., you can swing or thrust with
a short sword. Such weapons have multiple
lines on the weapon tables (pp. 20-22).
When you attack with a weapon like this,
you must indicate how you are using it
before you roll.
*/
/* NOTE: for information only.
 *
       A one-handed weapon is ready if it’s
   being held in your hand. A two-handed
   weapon is ready if you are gripping it with
   both hands. Some unwieldy weapons (e.g.,
   the poleaxe) become unready after each
   attack unless you are extremely strong (see
   p. 20).
        To draw a new weapon from a sheath,
   scabbard, or sling, or to ready an unwieldy
   weapon that became unready after an
   attack, you must take a Ready maneuver
   (p. 26).
   A natural weapon (punch, kick, etc.) is
   always ready unless the body part in question
   is occupied or restrained; e.g., you can’t
   punch if you are holding a weapon with the
   same hand.
*/

void Sand_Combat_Update(i32 monster_id)
{
    i32 player_id = 64;
    i32 damage;

    damage = Sand_Combat_Melee_Resolution(player_id, monster_id);
    if(damage > 0) printf("Player does %d Damage.\n", damage);
    Damage_Melee(ACTION_ATTACK, monster_id, damage);

    damage = Sand_Combat_Melee_Resolution(monster_id, player_id);
    if(damage > 0) printf("Monster does %d Damage.\n", damage);
    Damage_Melee(ACTION_ATTACK, player_id, damage);
}

i32 Sand_Combat_Target_Search(i32 actor, Attack_Target direction){

    if(direction < 1 || direction > 4 ){

        return 0;
    }

    Position* actors_position = (Position*)Object_Lookup_Component(
        actor,
        COMP_POSITION
    );
    // define variables
    float x_axis = actors_position->position[0];
    float z_axis = actors_position->position[2];
    Dungeon_Level_Current* current_dungeon = Dungeon_level();
    i32 object_at_location = 0;

    // target = direction facing/ 1 = north/ 2 = south/ 3 = west/ 4 = east
    // we can target and hit something beyond the line sight
    // Test the 1st space in that direction
    // if space exists the ask if there is a target-able object in that space

    if(direction == 1){

        // Search North = z_axis - 1
        z_axis --;
        // Test the 1st space in that direction etc
        while(current_dungeon->map_cells[(i32)x_axis][(i32)z_axis] &&
              object_at_location == 0){

            // if space exists the ask if there is a target-able object in that space
            object_at_location = Object_lookup_Wandering_Monster_location(
                (i32)x_axis,
                (i32)z_axis
            );

            if(object_at_location != 0) break;

            object_at_location = Object_lookup_Room_Monster_location(
                (i32)x_axis,
                (i32)z_axis
            );
        } // repeat until we have no space to target

    }else if (direction == 2){
        // TODO : copy code from above.
        // Search South = z_axis + 1
        // Test the 1st space in that direction
        // if space exists the ask if there is a target-able object in that space
        // repeat until we have no space to target

    }else if(direction == 3){

        // Search West x_axis - 1
        // Test the 1st space in that direction
        // if space exists the ask if there is a target-able object in that space
        // repeat until we have no space to target

    }else if(direction == 4){

        // Search East x_axis + 1
        // Test the 1st space in that direction
        // if space exists the ask if there is a target-able object in that space
        // repeat until we have no space to target

    }

    return object_at_location;
}

i32 Sand_Combat_Melee_Resolution(
    i32 attacker_id,
    i32 defender_id)
{
    /*
    Your “attack roll” is a regular success
    roll. Figure your effective skill (base skill
    plus or minus any appropriate modifiers)
    with the weapon you are using. */

    Monster_Stats* attacker = (Monster_Stats*)Object_Lookup_Component(
        attacker_id,
        COMP_MONSTER_STATS
    );

    Monster_Stats* defender = (Monster_Stats*)Object_Lookup_Component(
        defender_id,
        COMP_MONSTER_STATS
    );

//    Primary_Characteristics* primary = (Primary_Characteristics*)Object_Lookup_Component(
//        attacker_id,
//        COMP_PRIMARY_CHARACTERISTICS
//    );
//
//    Combat_Stats* combat = (Combat_Stats*)Object_Lookup_Component(
//        attacker_id,
//        COMP_COMBAT_STATS
//    );

    u8 attack_base_skill = attacker->attack_skill; // primary->dexterity;
    i32 attack_modifiers = attacker->shock; // combat->shock;

    i32 attack_roll;
    i32 effective_skill = attack_base_skill + attack_modifiers;

    /*
    If your roll is less than or equal to your
    “effective” skill, your attack will hit unless
    your foe successfully defends (see
    Defending, p. 28). If he fails to defend – or if
    he can’t – you’ve hit him.
    If your roll is greater than your effective
    skill, you missed!
     */
    bool attack_hits = false;

    attack_roll = Dice_Roll(3, 6);

    if(attack_roll <= effective_skill){
        attack_hits = true;
    }
    /*
    No matter what your skill, a roll of 3 or
    4 always hits, and is a critical hit. A roll of 5
    or 6 may be a critical hit, depending on
    your skill. If your effective skill is 15, then a
    roll of 5 or less is a critical hit. If your effective
    skill is 16 or more, then a roll of 6 or
    less is a critical hit.
    */
    bool critical_hit = false;

    critical_hit = Dice_Critical_Success(
        effective_skill,
        attack_roll
    );
    /*
    On a critical hit, the blow automatically
    hits home – your foe does not get a defense
    roll.
    */

    /*
    on an attack roll of 3, you do
    not roll for damage – your blow automatically
    does the most damage it could do. For
    instance, maximum damage for a 1d+2
    blow would be 6+2, or 8 points. Other critical
    hits bypass the defense roll, but roll
    normally for damage.
    */
    bool critical_max_damage = false;

    if(attack_roll == 3){
        critical_max_damage = true;
    }
    /*
    Regardless of skill, a roll of 17 or 18
    always misses.
    */
    bool critical_miss = false;

    critical_miss = Dice_Critical_Failure(effective_skill, attack_roll);

    if(critical_miss){
        attack_hits = false;
    }

    bool opponent_defends = false;
    /*
    Your foe does not get to attempt a defense
    roll if you rolled a critical hit against him.
    */
    if(critical_hit == false) {
        opponent_defends = Defence_Roll(defender);
    }

    if(opponent_defends){
        attack_hits = false;
    }

    /////////////////////////// Melee Attacks /////////////////////////
    /* enum Damage_Type
    Damage Type
    burning
    crushing
    cutting
    impaling
    small piercing
    piercing
    large piercing
    */
    //i32 melee_attack_damage_type = DAMAGE_CRUSHING;

    /*
    If his active
    defense was ineffective and the attack struck
    home.
    */

    i32 damage = 0;
    i32 damage_resistance = 1;

    if(attack_hits){
        // If this occurs, roll for damage.

        // 1D-2 for ST 9 Thrust for Punch
        damage = Dice_Roll(1, 6);
        damage = damage - 2;

        if(damage <= 1){
            damage = 1;
        }

        // cloth = Damage Resistance 1.
        damage = damage - damage_resistance;

        if(critical_max_damage){
            damage = 4;
        }
    }
    return damage;
}

i32 Sand_Combat_Ranged_Resolution(
    i32 attacker_id) {

    Monster_Stats* attacker = (Monster_Stats*)Object_Lookup_Component(attacker_id, COMP_MONSTER_STATS);

    // check for first target in that direction
    i32 defender_id = Sand_Combat_Target_Search(attacker_id, attacker->attack_target);
    Monster_Stats* defender = (Monster_Stats*)Object_Lookup_Component(defender_id, COMP_MONSTER_STATS);
    // roll to hit
    i32 attack_roll = Dice_Roll(3, 6);
    i32 effective_skill = attacker->attack_skill;

    bool critical_hit = false;

    critical_hit = Dice_Critical_Success(
        effective_skill,
        attack_roll
    );

    bool critical_max_damage = false;

    if(attack_roll == 3){
        critical_max_damage = true;
    }

    bool attack_hits = false;

    if(attack_roll <= effective_skill) {
        // roll defence
        attack_hits = true;
        if(Defence_Roll(defender)){

            attack_hits = false;
        }
    }

    bool critical_miss = false;

    critical_miss = Dice_Critical_Failure(effective_skill, attack_roll);

    if(critical_miss){
        attack_hits = false;
    }

    i32 damage = 1;

    if(attack_hits){

        damage = Dice_Roll(1, 6) + attacker->damage_ranged;
    }

    if (damage < 1){

        damage = 1;
    }

    // cloth = Damage Resistance 1.
    damage = damage - defender->damage_resistance;

    if(critical_max_damage){
        damage = 6 + attacker->damage_ranged;
    }
    //return damage
}


bool Defence_Roll(Monster_Stats* defender)
{
    /*
    Defense Roll
    The defender rolls 3d against his active
    defense score. If his roll is less than or equal
    to his effective defense, he dodged, parried,
    or blocked the attack. Otherwise, his active
    defense was ineffective and the attack struck
    home.
    */
//    Combat_Stats* combat = Object_Lookup_Component(
//        object_id,
//        COMP_COMBAT_STATS
//    );

    i32 active_defence_score = defender->dodge; // combat->dodge;
    /*
    If you are stunned, any active defense is at -4.

    If you have a ready shield, add its Defense
    Bonus (DB) to any Dodge, Parry, or Block
    roll against an attack that came from in front
    of you or from your shield side.
*/
    i32 active_defence_modifiers = 0;

    i32 effective_defence = active_defence_score +
        active_defence_modifiers;

    i32 defence_roll;

    defence_roll = Dice_Roll(3, 6);
    /*
    An active defense roll of 3 or 4 is always
    successful – even if your effective defense
    score was only 1 or 2! A roll of 17 or 18
    always fails.
    */
    if(defence_roll < 5){
        return true;
    }

    if(defence_roll > 16){
        return false;
    }

    if(defence_roll <= effective_defence){
        return true;
    }

    return false;
}
