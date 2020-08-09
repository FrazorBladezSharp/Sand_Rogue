//
// Created by frazor on 29/07/2020.
//
//! \brief the player is expected to earn 0-5 character points per level
//  with a bonus for completing a set number of levels.
//  so set 5 objectives per level

#include "Game_Objects.h"

static Vector vao_storage;
static Vector vbo_storage;

static Game_Object object[MAX_ENTITIES];
static Game_Entities game_entities[MAX_ENTITIES];
static Position position_component[MAX_ENTITIES];
static Game_Model model_component[MAX_ENTITIES];
static Primary_Characteristics primary_characteristic_component[MAX_ENTITIES];
static Secondary_Characteristics secondary_characteristic_component[MAX_ENTITIES];
static Combat_Stats combat_stats_component[MAX_ENTITIES];
static Monster_Stats monster_stats_component[MAX_ENTITIES];
//static Room_Contents room_contents[MAX_ROOM_CONTENTS];

void Object_Initialize()
{
    Vector_init(
        &vao_storage                // initialize OpenGL handle storage
    );

    Vector_init(
        &vbo_storage                // used to delete Gfx Card buffers
    );

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize Entities

        game_entities->entity_id[index] = UNUSED;            // set all entities to unused
        object[index].object_id = UNUSED;                    // set all objects to unused
    }

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize components

        position_component[index].object_id = UNUSED;       // clear all component id's
        model_component[index].object_id = UNUSED;
        primary_characteristic_component[index].object_id = UNUSED;
        secondary_characteristic_component[index].object_id= UNUSED;
        combat_stats_component[index].object_id = UNUSED;
        monster_stats_component[index].object_id = UNUSED;
    }

    Monsters_Initialize_Models(
        &vao_storage,
        &vbo_storage,
        &model_component[0],
        &object[0]
    );

    Monsters_Data_Initialize();

    // Create the player
    u32 room = 0;
    i32 player_id;
    player_id = Object_Create(64, 64);

    Object_Add_Position(
        player_id,
        room
    );

    Object_Add_Primary_Characteristics(
        player_id
    );

    Object_Add_Secondary_Characteristics(
        player_id
    );

    Object_Add_Combat_Stats(
        player_id
    );

    // create the monsters
    for (u8 index = 64; index < 91; index++){

        Object_Add_Monster_Stats(
            index
        );
    }


    //i32 number_of_dungeon_rooms = Map_Number_Of_Rooms();


}

i32 Object_Create(
        i32 index,
        i32 ascii_character) {

    game_entities->entity_id[index] = ascii_character;         // register object as an entity
    object[index].object_id = ascii_character;                 // assign the object an entity id

    return index;
}
    //////////////////////// Position Component //////////////////////////
void Object_Add_Position(
    i32 object_id,
    u32 room) {


        Position *object_position;

        object_position = (Position *) malloc(
            sizeof(Position)
        );

        object_position->object_id = object_id;          // set values for the object position.

        Point_3D placement = Map_Random_Point_In_Room(
            room
        );

        object_position->position[0] = (float) placement.x;                   // initialize all to effective zero
        object_position->position[1] = 0.5f;
        object_position->position[2] = (float) placement.z;
        object_position->rotationX = 0.0f;
        object_position->rotationY = -45.0f;
        object_position->rotationZ = 0.0f;
        object_position->scale = 1.0f;

        position_component[object->object_id].object_id = object_id;    // keep track of all position components
        object[object_id].component[COMP_POSITION] = object_position;   // add position component to object
    }
    ////////////////////////// Model Component ///////////////////////////
    /*
void Object_Add_Model(
        i32 object_id,
        vec4 color,
        const char* file_path) {


        Game_Model *object_model;

        object_model = Load_Model_3D(   // memory is allocated by the model loader.
            file_path,
            color,
            &vao_storage,
            &vbo_storage
        );

        object_model->object_id = object_id;

        model_component[object->object_id].object_id = object_id;
        object[object_id].component[COMP_MODEL] = object_model;
    }
     */
    ///////////////////// Primary Characteristics Component ///////////////////////////////
void Object_Add_Primary_Characteristics(i32 object_id) {


        Primary_Characteristics *primary;

        primary = (Primary_Characteristics *) malloc(
            sizeof(Primary_Characteristics)
        );

        primary[object_id].object_id = object_id;

        primary->object_id = object_id;
        primary->strength = 9;
        primary->strength_cost = -10;
        primary->dexterity = 9;
        primary->dexterity_cost = -20;
        primary->intelligence = 9;
        primary->intelligence_cost = -20;
        primary->health = 9;
        primary->health_cost = -10;
        primary->health_status = HEALTH_STATUS_NONE;

        primary_characteristic_component[object->object_id].object_id = object_id;
        object[object_id].component[COMP_PRIMARY_CHARACTERISTICS] = primary;
    }
    //////////////////// Secondary Characteristics Component ////////////////////////////////
void Object_Add_Secondary_Characteristics(i32 object_id) {

        Secondary_Characteristics *secondary;

        secondary = (Secondary_Characteristics *) malloc(
            sizeof(Secondary_Characteristics)
        );

        secondary[object_id].object_id = object_id;

        secondary->object_id = object_id;
        secondary->hit_points_max = 9;
        secondary->hit_points_cost = 0;
        secondary->hit_points_current = 9;
        secondary->will = 9;
        secondary->perception = 9;
        secondary->fatigue_points = 9;
        secondary->basic_move = 4;
        secondary->base_speed = 4.25;
        secondary->action_current = ACTION_NONE;

        secondary_characteristic_component[object->object_id].object_id = object_id;
        object[object_id].component[COMP_SECONDARY_CHARACTERISTICS] = secondary;
    }
    //////////////////// Combat Stats Component ////////////////////////////////
void Object_Add_Combat_Stats(i32 object_id) {

        Combat_Stats *combat;

        combat = (Combat_Stats *) malloc(
            sizeof(Combat_Stats)
        );

        combat[object_id].object_id = object_id;

        combat->object_id = object_id;
        combat->thrust_damage = 1;
        combat->thrust_damage_modifier = -2;
        combat->swing_damage = 1;
        combat->swing_damage_modifier = -1;
        combat->damage_resistance = 1;
        combat->dodge = 7;
        combat->parry = 9;
        combat->block = 3;
        combat->shock = 0;

        combat_stats_component[object->object_id].object_id = object_id;
        object[object_id].component[COMP_COMBAT_STATS] = combat;
    }
    //////////////////////////// Monster Stats /////////////////////////////////////

void Object_Add_Monster_Stats(i32 object_id) {

    Monster_Stats *monster;

    monster = (Monster_Stats *) malloc(
        sizeof(Monster_Stats)
    );

    monster[object_id].object_id = object_id;


    strcpy(monster->name, Monsters_Name(object_id));
    monster->health_status = Monsters_Health_Status(object_id);
    monster->treasure = Monsters_Treasure(object_id);
    monster->AI_to_use = Monsters_AI_To_Use(object_id);
    monster->will = Monsters_Will(object_id);
    monster->base_speed = Monsters_Base_Speed(object_id);
    monster->unit_xp = Monsters_Unit_Xp(object_id);
    monster->hit_points_max = Monsters_Hit_Points_Max(object_id);
    monster->hit_points_current = Monsters_Hit_Points_Current(object_id);
    monster->damage_resistance = Monsters_Damage_Resistance(object_id);
    monster->dodge = Monsters_Dodge(object_id);
    monster->attack_skill = Monsters_Attack_Skill(object_id);
    monster->special_attack = Monsters_Special_Attack(object_id);
    monster->damage_type = Monsters_Damage_Type(object_id);
    monster->damage_melee = Monsters_Damage_Melee(object_id);
    monster->damage_ranged = Monsters_Damage_Ranged(object_id);
    monster->shock = Monsters_Shock(object_id);



    monster_stats_component[object->object_id].object_id = object_id;
    object[object_id].component[COMP_MONSTER_STATS] = monster;
}

//////////////////////////////////////////////////////////////////////

void* Object_Lookup_Component(
    i32 object_id,
    i32 component)
{
    return object[object_id].component[component];
}

void Object_Add_VAO(GLint data)
{
    Vector_append(
        &vao_storage,
        data
    );
}
void Object_Add_VBO(GLint data)
{
    Vector_append(
        &vbo_storage,
        data
    );
}

void Object_Cleanup()
{
    // delete all vao's that have been created
    printf(
        "Deleting VAO vectors: %d\n",
        Vector_size(&vao_storage)
    );

    for (int index = 0; index < Vector_size(&vao_storage); index++) {

        GLuint vao = Vector_get(
            &vao_storage,
            index
        );

        glDeleteVertexArrays(
            1,
            (GLuint *) &vao
        );
    }

    Vector_free_memory(
        &vao_storage
    );

// delete all vbo's that were created.

    printf(
        "Deleting VBO vectors: %d\n",
        Vector_size(&vbo_storage)
    );

    for (int index = 0; index < Vector_size(&vbo_storage); index++) {

        GLuint vbo = Vector_get(
            &vbo_storage, index
        );

        glDeleteBuffers(
            1,
            (GLuint *) &vbo
        );
    }

    Vector_free_memory(&vbo_storage);
}

#define MAX_ITEMS 1024

static const char* game_items[MAX_ITEMS];
static i32 game_item_value[MAX_ITEMS];
static bool game_weapon_damage[9];
static Damage_Type game_weapon_damage_type[9];

void Game_Items_Initialize() {
/*
 * convert to G.U.R.P.S.
 * AC = AC - 2 first column works for our system
Armor @ 0 ]
Name	        AC (v5)	AC  %Drop
Leather	        3	    8   20 = 20
Ring mail	    4	    7   35 = 15
Studded leather	4	    7   50 = 15
Scale mail	    5   	6   63 = 13
Chain mail	    6   	5   75 = 12
Splint mail	    7   	4   85 = 10
Banded mail	    7   	4   95 = 10
Plate mail	    8   	3   100 = 5

A higher AC gives a better chance to avoid damage.
TODO : Armor drop chance.
Older versions of Rogue used the decreasing AC to represent better armor (also shown in the table).
*/
    game_items[0] = "Light Leather Clothing";
    game_item_value[0] = 1;

    game_items[1] = "Ring Mail Armour";
    game_item_value[1] = 2;

    game_items[2] = "Studded Leather Armour";
    game_item_value[2] = 2;

    game_items[3] = "Scale Mail Armour";
    game_item_value[3] = 3;

    game_items[4] = "Chain Mail Armour";
    game_item_value[4] = 4;

    game_items[5] = "Splint Mail Armour";
    game_item_value[5] = 5;

    game_items[6] = "Banded Mail Armour";
    game_item_value[6] = 5;

    game_items[7] = "Plate Mail Armour";
    game_item_value[7] = 6;

 ///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @ 10 )           TODO: Drop 10% each
Weapon	            Damage  G.U.R.P.S.      Notes
Mace	            2d4     swing + 3 cr
Long sword	        3d4     swing + 1 cut
Short bow	        1d1     swing - 4 cr
Arrow	            2d3     thrust imp      Takes bonuses from equipped short bow.
Dagger	            1d6	    thrust imp
Two handed sword	4d4     swing + 4 cut
Dart	            1d3     thrust - 3 imp
Shuriken	        2d4     thrust + 2 imp
Spear	            2d3	    thrust + 3 imp
*/
    game_items[10] = "Mace";
    game_item_value[10] = 3;
    game_weapon_damage[0] = false;
    game_weapon_damage_type[0] = DAMAGE_CRUSHING;

    game_items[11] = "Long Sword";
    game_item_value[11] = 1;
    game_weapon_damage[1] = false;
    game_weapon_damage_type[0] = DAMAGE_CUTTING;

    game_items[12] = "Short Bow";
    game_item_value[12] = -4;
    game_weapon_damage[2] = false;
    game_weapon_damage_type[0] = DAMAGE_CRUSHING;

    game_items[13] = "Arrow";
    game_item_value[13] = 0;
    game_weapon_damage[3] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

    game_items[14] = "Dagger";
    game_item_value[14] = 0;
    game_weapon_damage[4] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

    game_items[15] = "Two Handed Sword";
    game_item_value[15] = 4;
    game_weapon_damage[5] = false;
    game_weapon_damage_type[0] = DAMAGE_CUTTING;

    game_items[16] = "Dart";
    game_item_value[16] = -3;
    game_weapon_damage[6] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

    game_items[17] = "Shuriken";
    game_item_value[17] = 2;
    game_weapon_damage[7] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

    game_items[18] = "Spear";
    game_item_value[18] = 3;
    game_weapon_damage[8] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

 //////////////////////////////////////////////////////////////////////////////////////////////////
/*
 Rings @ 61 '='
Item	%chance	Description
protection	        9	Adds to defense and magical saving throws
Add strength	    9	Adds to strength
Sustain strength	5	Prevents poison from reducing strength
Searching	        10	Helps detect secret doors and traps.
See invisible	    10	Reveals Phantoms.
Adornment	        1	Worth 10 gold.
Aggravate monster	10	Cursed. Causes monsters to attack more aggressively.
Dexterity	        8	Improves weapon accuracy.
Increase damage	    8	Increases weapon damage.
Regeneration	    4	Heals 1 hp per turn
Slow digestion	    9	Reduces food consumption by about 50%. Two rings can cancel out food consumption.
Teleportation	    5	Cursed. Randomly teleports the player around the map.
Stealth	            7	Allows player to move without rousing sleeping monsters.
Maintain armor	    5	Prevents rust damage

The rings that provide bonuses may either give +1 or +2, but can also be cursed and give -1 instead.
*/
    game_items[20] = "Protection";
    game_item_value[20] = 9;

    game_items[21] = "Add Strength";
    game_item_value[21] = 9;

    game_items[22] = "Sustain Strength";
    game_item_value[22] = 5;

    game_items[23] = "Searching";
    game_item_value[23] = 10;

    game_items[24] = "See Invisible";
    game_item_value[24] = 10;

    game_items[25] = "Adornment";
    game_item_value[25] = 1;

    game_items[26] = "Aggravate Monster";
    game_item_value[26] = 10;

    game_items[27] = "Dexterity";
    game_item_value[27] = 8;

    game_items[28] = "Increase Damage";
    game_item_value[28] = 8;

    game_items[29] = "Regeneration";
    game_item_value[29] = 4;

    game_items[30] = "Slow Digestion";
    game_item_value[30] = 9;

    game_items[31] = "Teleportation";
    game_item_value[31] = 5;

    game_items[32] = "Stealth";
    game_item_value[32] = 7;

    game_items[33] = "Maintain Armour";
    game_item_value[33] = 5;

 /////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 Potions @ 40 !
Item	        %chance	Description
Confusion	        7	Confuses the player for 19-21 turns
Hallucination	    8	Causes hallucinations for 850 turns - can't recognize monsters or items
Poison	            8	Reduces strength by 1-3 points.
Gain strength	    13	Increases strength by 1.
See invisible	    3	This potion tastes like slime mold juice. Reveals Phantoms.
Healing	            13	Heals 1df per character level. Increase max HP by 1 if you are at full health.
Monster detection	6	Reveals monsters on the map.
Magic detection	    6	Reveals magic items on the map.
Raise level	        2	Increases experience level by 1.
Extra healing	    5	Heals 1d8 per character level. Increase max HP by 1, or by 2 if you are at full health.
Haste self	        5	Hastens player for 4-8 turns.
Restore strength	13	Hey, this tastes great. It make you feel warm all over. Restores strength to maximum.
Blindness	        5	Blinds player for 807-892 turns
Levitation	        6	Levitates for 29-32 turns
*/
    game_items[40] = "Confusion";
    game_item_value[40] = 7;

    game_items[41] = "Hallucination";
    game_item_value[41] = 8;

    game_items[42] = "Poison";
    game_item_value[42] = 8;

    game_items[43] = "Gain Strength";
    game_item_value[43] = 13;

    game_items[44] = "See Invisible";
    game_item_value[44] = 3;

    game_items[45] = "Healing";
    game_item_value[45] = 13;

    game_items[45] = "Monster Detection";
    game_item_value[45] = 6;

    game_items[45] = "Magic Detection";
    game_item_value[45] = 6;

    game_items[45] = "Raise Level";
    game_item_value[45] = 2;

    game_items[45] = "Extra Healing";
    game_item_value[45] = 5;

    game_items[45] = "Haste Self";
    game_item_value[45] = 5;

    game_items[45] = "Restore Strength";
    game_item_value[45] = 13;

    game_items[45] = "Blindness";
    game_item_value[45] = 5;

    game_items[45] = "Levitation";
    game_item_value[45] = 6;

 //////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 Rods 50 /
Rods can either be wands or staffs. While there are differences between them, they are minor.

Item	%chance	Description
Light	        12	Has 10-19 charges. Illuminates the room.
Invisibility	6	Makes a monster invisible.
Lightning	    3	Inflicts 6d6 damage for up to 6 tiles. Bounces off walls.
Fire	        3	Inflicts 6d6 damage for up to 6 tiles. Bounces off walls. Dragons are immune.
Cold	        3	Inflicts 6d6 damage for up to 6 tiles. Bounces off walls. Yetis are immune.
Polymorph	    15	Changes a monster type.
Magic missile	10	Inflicts 1d4 damage on a single target.
Haste monster	10	Hastens a monster.
Slow monster	11	Slows a monster.
Drain life	    9	Drains half of the hero's hp, then removes the same amount of health evenly from visible monsters.
Nothing	        1	Doesn't do anything.
Teleport away	6	Teleports a monster randomly on the map.
Teleport to	    6	Causes the monster to teleport next to the player.
Cancellation	5	Suppresses monster's special abilities.

Staves normally appear with 3-7 charges.
*/
    game_items[50] = "Light";
    game_item_value[50] = 12;

    game_items[51] = "Invisibility";
    game_item_value[51] = 6;

    game_items[52] = "Lightning";
    game_item_value[52] = 3;

    game_items[53] = "Fire";
    game_item_value[53] = 3;

    game_items[54] = "Cold";
    game_item_value[54] = 3;

    game_items[55] = "Polymorph";
    game_item_value[55] = 15;

    game_items[56] = "Magic Missile";
    game_item_value[56] = 10;

    game_items[57] = "Haste Monster";
    game_item_value[57] = 10;

    game_items[58] = "Slow Monster";
    game_item_value[58] = 11;

    game_items[59] = "Drain Life";
    game_item_value[59] = 9;

    game_items[60] = "Nothing";
    game_item_value[60] = 1;

    game_items[61] = "Teleport Away";
    game_item_value[61] = 6;

    game_items[62] = "Teleport To";
    game_item_value[62] = 6;

    game_items[63] = "Cancellation";
    game_item_value[63] = 5;

 /////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 Scrolls @ 70 ?
Item	                    %chance	Description
Monster confusion	            7	Your hands begin to glow red. Next melee attack confuses a monster.
Magic mapping	                4	Reveals the entire map; objects are still hidden
Hold monster	                2	Freezes adjacent monsters.
Sleep	                        3	Sleeps reader for 4-8 turns.
Enchant armor	                7	Your armor glows silver for a moment. Improved protection by 1.
Identify potion	                10	Identifies a potion.
Identify scroll	                10	Identifies a scroll.
Identify weapon	                6	Identifies a weapon.
Identify armor	                7	Identifies a suit of armor.
Identify ring, wand or staff	10	Identifies a ring, wand or staff.
Scare monster	                3	When read, you hear maniacal laughter in the distance. To properly use the scroll, drop it; monsters will not walk on it.
Food detection	                2	Your nose tingles. Detects food on the current level.
Teleportation	                5	Teleports to a random location on the map.
Enchant weapon	                8	Your (weapon) glows blue for a moment. Increases hit or damage bonus by 1.
Create Monster	                4	Summons a monster on an adjacent tile. If it fails, you hear a faint cry of anguish in the distance.
Remove curse	                7	You feel as if somebody is watching over you. Removes curses from equipped items.
Aggravate monsters	            3	You hear a high pitched humming noise.. Alerts all monsters on the map.
Protect armor	                2	Your armor is covered by a shimmering gold shield. Prevents rust damage from aquators.

Some scrolls require certain conditions to be met. If they aren't, you see the message "you feel a strange sense of loss".
*/
    game_items[70] = "Monster Confusion";
    game_item_value[70] = 7;

    game_items[71] = "Magic Mapping";
    game_item_value[71] = 4;

    game_items[72] = "Hold Monster";
    game_item_value[72] = 2;

    game_items[73] = "Sleep";
    game_item_value[73] = 3;

    game_items[74] = "Enchant Armor";
    game_item_value[74] = 7;

    game_items[75] = "Identify Potion";
    game_item_value[75] = 10;

    game_items[76] = "Identify Scroll";
    game_item_value[76] = 10;

    game_items[77] = "Identify Weapon";
    game_item_value[77] = 6;

    game_items[78] = "Identify Armor";
    game_item_value[78] = 7;

    game_items[79] = "Identify Ring, Wand or Staff";
    game_item_value[79] = 10;

    game_items[80] = "Scare Monster";
    game_item_value[80] = 3;

    game_items[81] = "Food Detection";
    game_item_value[81] = 2;

    game_items[82] = "Teleportation";
    game_item_value[82] = 5;

    game_items[83] = "Enchant Weapon";
    game_item_value[83] = 8;

    game_items[84] = "Create Monster";
    game_item_value[84] = 4;

    game_items[81] = "Remove Curse";
    game_item_value[81] = 7;

    game_items[81] = "Aggravate Monsters";
    game_item_value[81] = 3;

    game_items[81] = "Protect Armor";
    game_item_value[81] = 2;

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

// TODO: add room Contents when door is opened
// Room_Contents. room_contents[index] room = dark (rnd(10) < (level - 1))
// MAX CONTENTS PER LEVEL max things = num rooms  max objects = num_rooms
// things = stairs doors gold & objects
// objects = items 35% per max_object then pick random object
// items & location

// chance per room (rnd(100) < (gold value > 0 ? 80 : 25))

// armour TODO : as above location  93          ]       object cycle through objects to place them
// weapon TODO: as above location   41          )       object
// rings TODO: as above             92          \       object
// potions TODO : as above location 33          !       object
// rods & staves TODO: as above     47          /       object
// scrolls TODO: as above           63          ?       object

// food TODO: as above              58          :       object
// gold TODO: as above              42          *  #define GOLD_CALC (rnd(50 + 10 * level) + 2)
// chance per room ((rnd(3) == 3) && (! has not seen amulet || (level >= max_level))) thing = gold
// stairs down TODO: as above       62          >       thing
// stairs up TODO: as above         60          <       thing
// Trap TODO: as above              94          ^       thing

/* TODO: Objects Update
void Objects_Update( //              NOTE This can all be done in Game_Objects
    i8 current_dungeon_level){      // add and remove objects from line of sight

    //distribute monsters across the level. chance per room + wandering extra chance
* how many ? = how many have been seen
 * monsters_added = 0
 *
 * add a monster
 *
 * copy its stats to the monster list for the level (101)
     TODO : initialize a new dungeon level
    */

// generate a new monster as required
