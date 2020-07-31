//
// Created by frazor on 31/07/2020.
//

#include "Sand_Combat.h"

/* TODO: (Frazor) move this rule to the main update loop ??
Melee Attacks
When you take a maneuver that lets you
make a melee attack, you must specify who
you are attacking, and with what weapon.
*/
/* (Frazor) we can place an enum in the header file to cover this
 * TODO : (Frazor) does the enum go in Common.h  or in this header file.
You can make a melee attack using any
ready melee weapon (including a natural
weapon such as a kick, bite, or punch).
You can use some weapons in more than
one way; e.g., you can swing or thrust with
a shortsword. Such weapons have multiple
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
   always ready unless the body part in ques-
   tion is occupied or restrained; e.g., you can’t
   punch if you are holding a weapon with the
   same hand.
*/


i32 Sand_Attack_Roll()
{
    /*
    Your “attack roll” is a regular success
    roll. Figure your effective skill (base skill
    plus or minus any appropriate modifiers)
    with the weapon you are using. */

    i32 attack_base_skill = 9; // Brawling base skill 1 = dex
    i32 attack_modifiers = 0;

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
    roll of 5 or less is a critical hit. If your effec-
    tive skill is 16 or more, then a roll of 6 or
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
    not roll for damage – your blow automati-
    cally does the most damage it could do. For
    instance, maximum damage for a 1d+2
    blow would be 6+2, or 8 points. Other crit-
    ical hits bypass the defense roll, but roll
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
        opponent_defends = Defence_Roll();
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
        damage = Dice_Roll(1, 6) - 2;

        if(damage < 1){
            damage = 1;
        }

        // cloth = Damage Resistance 1.
        damage -= damage_resistance;

        if(damage < 1){
            damage = 1;
        }

        if(critical_max_damage){
            damage = 4;
        }

    }

    return damage;
}



bool Defence_Roll()
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
    i32 active_defence_score = 8; // basic dodge speed for stats @ 9
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