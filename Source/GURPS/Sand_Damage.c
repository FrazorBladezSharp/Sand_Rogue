//
// Created by frazor on 04/08/2020.
//

#include "Sand_Damage.h"


void Damage_Melee(
    Action opponents_action,
    i32 object_id,
    i32 damage)
{
    // damage here is after DR has been applied.
    /*
    This is a multiplier that depends on
    damage type:
    • Small piercing (pi-): * 0.5.
    • Cutting (cut) and large piercing (pi+):
    * 1.5.
    . Crushing: * 1.0
    • Impaling (imp): * 2.0

        The damage after this multiplier deter-
        mines the injury: the HP lost by the target.
        Round fractions down, but the minimum
    injury is 1 HP for any attack that penetrates
    DR at all. Reduce the victim’s current HP
    total by the injury sustained.
    */
    Primary_Characteristics* primary = (Primary_Characteristics*) Object_Lookup_Component(
        object_id,
        COMP_PRIMARY_CHARACTERISTICS
    );

    Secondary_Characteristics* secondary = (Secondary_Characteristics*) Object_Lookup_Component(
        object_id,
        COMP_SECONDARY_CHARACTERISTICS
    );

    Combat_Stats* combat = (Combat_Stats*) Object_Lookup_Component(
        object_id,
        COMP_COMBAT_STATS
    );

    if(damage <= 0) {

        if(primary->health_status == HEALTH_STATUS_SHOCK){

            primary->health_status = HEALTH_STATUS_NONE;
        }

        return;

    }else if(primary->health_status == HEALTH_STATUS_NONE){

        primary->health_status = HEALTH_STATUS_SHOCK;
    }

    i32 health = primary->health;

    secondary->hit_points_current -= damage;
    /*
     All effects are cumulative.
     Less than 1/3 your HP left – You are reeling
     from your wounds. Halve your Move
     and Dodge (round up).
     */
    if(secondary->hit_points_current < secondary->hit_points_max / 3){

        secondary->basic_move /= 2;
        combat->dodge /= 2;
    }
    /*
     0 HP or less – You are in immediate danger
     of collapse. In addition to the above
     effects, make a HT roll at the start of
    your next turn, at -1 per full multiple of
    HP below zero. Failure means you fall
    unconscious (or simply stop working, if
    you weren't truly alive or conscious in
    the first place); see Recovering from
    Unconsciousness (p. 30). Success means
    you can act normally, but must roll
    again every turn to continue functioning.
    Exception: If you choose Do Nothing on
    your turn, and do not attempt any
    defense rolls, you can remain conscious
    without rolling. Roll only on turns dur-
    ing which you attempt a defense roll or
    choose a maneuver other than Do
    Nothing.
    */
    i32 multiple_negative_hp =
        secondary->hit_points_current / health;

    if(secondary->hit_points_current <=0 &&
        opponents_action != ACTION_NONE){

        printf("Object %d makes a health roll (Negative Hp)\n", object_id);

        primary->health_status = Damage_Health_Roll(
            health,
            multiple_negative_hp,
            HEALTH_STATUS_UNCONCIOUS
        );
    }
    /*
    -1 * HP – In addition to the above effects,
    make an immediate HT roll or die. (If
    you fail by only 1 or 2, you’re dying, but
    not dead – see Mortal Wounds, below). If
    you succeed, you can still talk, fight, etc.,
    as above (until you fail a HT roll and col-
    lapse). Roll again each time you suffer
    injury equal to a further multiple of your
    HP, whether as a result of one wound or
    many. For instance, if you have 11 HP,
        you must roll to avoid death at -11 HP. If
    you survive, you must roll again at -22
    HP, -33 HP, and so on . . .
     */
    if((secondary->hit_points_current <= ((-1 + multiple_negative_hp) * health)) &&
      ((secondary->hit_points_current > ((-2 + multiple_negative_hp) * health)))){

        printf("Object %d makes a health roll (Death)\n", object_id);
        primary->health_status = Damage_Health_Roll(
            health,
            0,
            HEALTH_STATUS_DEATH
        );

        return;
    }
    /*
    -5 * HP – You die immediately.
    You have lost a total of 6 times your HP! Nobody can
    survive that much injury.
     */
    if(secondary->hit_points_current <= (-5 * health)){

        primary->health_status = HEALTH_STATUS_DEATH;

        return;
    }
    /*
    -10 * HP – Total bodily destruction, if this
    makes sense given the source of the damage.
    eg 200 points of arrow wounds
    leave a messy but recognizable corpse;
    eg 200 points of fire injury leaves nothing
    but an unrecognizable lump of charcoal.

    The difference can be important in settings
    where resurrection, reanimation, etc. are possible!
    */

    // Rogue is permanent death so no need to take an action.

    /*
    Shock
    Whenever you suffer injury, reduce your
    DX and IQ by the number of HP you lost –
    to a maximum penalty of -4, regardless of
    your injuries – on your next turn only. This
    effect, called “shock,” is temporary; your
    attributes return to normal on the turn after
    that.
        Shock affects DX- and IQ-based skills,
    but not active defenses or other defensive
    reactions.
    */
    i32 shock_generated = -1 * damage;

    if(shock_generated <= -4){

        shock_generated = -4;
    }

    combat->shock = shock_generated;
    /*
    Major Wounds
    A “major wound” is any single injury of
    greater than 1/2 your HP. Any major wound
    requires a HT roll to avoid knockdown and
    stunning (see below).
    */
    if(damage > health / 2){

        printf("Object %d makes a health roll (Major Wounds)\n", object_id);
        primary->health_status = Damage_Health_Roll(
            health,
            0,
            HEALTH_STATUS_MAJOR_WOUNDS
        );
    }

    if(primary->health_status == HEALTH_STATUS_MORTAL_WOUNDS){

        printf("Object %d makes a health roll (Mortal Wounds)\n", object_id);
        primary->health_status = Damage_Health_Roll(
            health,
            0,
            HEALTH_STATUS_MORTAL_WOUNDS
        );
    }
}

Health_Status Damage_Health_Roll(
    i32 health,
    i32 modifier,
    Health_Status type)
{
    bool unconcious = false;

    int dice_roll = Dice_Roll(3, 6);

    printf("\n dice roll %d : (Unconcious)\n", dice_roll);
    if(type == HEALTH_STATUS_UNCONCIOUS){

        printf("\t\t v unconcious = %d\n", dice_roll);

        if(dice_roll > health + modifier){

            unconcious = true;
        }
    }

    dice_roll = Dice_Roll(3, 6);

    printf("\n dice roll %d (Death plus others) \n", dice_roll);

    if(dice_roll > (health + 2)){

        return HEALTH_STATUS_DEATH;

    }else if (dice_roll > health){

        return HEALTH_STATUS_MAJOR_WOUNDS;
    }

    if(type == HEALTH_STATUS_MAJOR_WOUNDS){

        /*
         This effect is called “knockdown.” On a failure
         by 5 or more, or any critical failure, you
        fall unconscious!
         */
        bool critical_failure = Dice_Critical_Failure(
            health,
            dice_roll
        );

        if(critical_failure || dice_roll >= health + 5){

            return HEALTH_STATUS_UNCONCIOUS;
        }

        if(dice_roll > health){

            return HEALTH_STATUS_KNOCKDOWN_AND_STUN;
        }

    }else if(type == HEALTH_STATUS_MORTAL_WOUNDS){

        return HEALTH_STATUS_DEATH;
    }

    if(unconcious){

        return HEALTH_STATUS_UNCONCIOUS;
    }

    return HEALTH_STATUS_NONE;
}