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
static Combat_Stats combat_stats[MAX_ENTITIES];
static Room_Contents room_contents[MAX_ROOM_CONTENTS];


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
        combat_stats[index].object_id = UNUSED;
    }

    vec4 color_green = { 0.1f, 0.5f, 0.1f, 1.0f };  // test colors for our 2 3D Models
    vec4 color_red =   { 0.5f, 0.1f, 0.1f, 1.0f };

    Object_Create(                                  // create the player
        64,                             // ascii for @ character
        color_green,
        0,
        "Resource/Models/Player.obj"
    );

    Object_Create(                                  // create the monster
        77,                             // ascii for M character
        color_red,
        1,
        "Resource/Models/Monster.obj"
    );
    /*
    Monsters
    List of Monsters (Original)
    Name	    Treasure	Flags	Exp	    HP	    AC	Damage	    Range	Notes
    Aquator	        0	    M	    20	    5d8	    2	0d0/0d0		        Rusts armor
    Bat	            0	    F	    1	    1d8	    3	1d2		            Flies randomly
    Centaur	        15		17	    4d8	    4	        1d2/1d5/1d5
    Dragon	        100	    M	    5000    10d8	-1	1d8/1d8/3d10		Ranged 6d6 flame attack
    Emu	            0	    M	    2	    1d8	    7	1d2
    Venus Flytrap	0	    M	    80	    8d8	    3	special		        Traps player
    Griffin	        20	    MFR	    2000	13d8	2	4d3/3d5
    Hobgoblin	    0	    M	    3	    1d8	    5	1d8
    Ice monster	    0		        5	    1d8	    9	0d0		            Freezes player
    Jabberwock	    70		        3000	15d8	6	2d12/2d4
    Kestrel	        0	    MF	    1	    1d8	    7	1d4
    Leprechaun	    0		        10	    3d8	    8	1d1		            Steals gold
    Medusa	        40	    M	    200	    8d8	    2	3d4/3d4/2d5		    Confuses Hero
    Nymph	        100		        37	    3d8	    9	0d0		            Steals magic item
    Orc	            15	    G	    5	    1d8	    6	1d8		            Greedy - runs toward gold
    Phantom	        0	    I	    120	    8d8	    3	4d4		            Invisible
    Quagga	        0	    M	    15	    3d8	    3	1d5/1d5
    Rattlesnake	    0	    M	    9	    2d8	    3	1d6		            Reduces Strength
    Snake	        0	    M	    2	    1d8	    5	1d3
    Troll	        50	    RM	    120	    6d8	    4	1d8/1d8/2d6
    Ur-vile	        0	    M	    190	    7d8	    -2	1d9/1d9/2d9
    Vampire	        20	    RM	    350	    8d8	    1	1d10		        Drains Max HP
    Wraith	        0		        55	    5d8	    4	1d6		            Drains exp
    Xeroc	        30		        100	    7d8	    7	4d4		            Imitates an object
    Yeti	        30		        50	    4d8	    6	1d6/1d6
    Zombie	        0	    M	    6	    2d8	    8	1d8

    Level is the level of Hit dice for the monster.
        AC is the monster's armor class. A monster with lower AC is harder to hit.
    Treasure is the percent chance that a monster will be carrying treasure.

        M for "mean". Mean monsters may attack without provocation.
        F for "flying". Flying monsters are more difficult to hit.
        R for "regeneration". These monsters can regenerate health.
        G for "greedy". Greedy monsters attempt to pick up gold when you enter a room.
        I for "invisible".
    */

    i32 number_of_dungeon_rooms = Map_Number_Of_Rooms();

    // Room_Contents. room_contents[index]
    // items & location

    // monster TODO: ecs with location
    // armour TODO: use ecs we need to refactor Object_Create() into individual functions
    // weapon TODO: as above
    // rings TODO: as above
    // potions TODO : as above
    // rods & staves TODO: as above
    // scrolls TODO: as above


    // decide which monsters are available for this level.
    // we need to go through all eligible monsters and add then to the level
    // TODO: (Frazor) NOTE : set a max number of monsters / items per level
    // add monsters and items to random rooms (placement. - we already have a function in map)


    //////// Test code ////////
    // this shows that we can detect if an entity exits and if its object exists
    // Also Object_lookup_Component() will return an objects components.
    ///////////////////////////
    for(i32 index = 0; index < MAX_ENTITIES; index++){

        if(object[index].object_id != UNUSED){

            Game_Model* current = (Game_Model*)Object_Lookup_Component(
                index,
                COMP_MODEL
            );

            printf(
                "Object does exist %d : ",
                object[index].object_id
            );

            printf(
                "With model number %d\n",
                current->object_id
            );
        }
    }

    for(i32 object_index = 0; object_index < MAX_ENTITIES; object_index++){

        if(game_entities->entity_id[object_index] != UNUSED){

            printf(
                "Entity %d exists !\n",
                object_index
            );
        }
    }
    //////////// End Tests ////////////////
}

void Object_Create(
    i32 ascii_character,
    vec4 color,
    u32 starting_room,
    const char* file_path)
{
    game_entities->entity_id[ascii_character] = ascii_character;         // register object as an entity
    object[ascii_character].object_id = ascii_character;                 // assign the object an entity id

    // NOTE: you must free the memory before game exit      *** NOTE ****
    //////////////////////// Position Component //////////////////////////

    Position *object_position;

    object_position = (Position *) malloc(
        sizeof(Position)
    );

    object_position->object_id = ascii_character;          // set values for the object position.

    Point_3D placement = Map_Random_Point_In_Room(
        starting_room
    );

    object_position->position[0] = (float)placement.x;                   // initialize all to effective zero
    object_position->position[1] = 0.5f;
    object_position->position[2] = (float)placement.z;
    object_position->rotationX = 0.0f;
    object_position->rotationY = -45.0f;
    object_position->rotationZ = 0.0f;
    object_position->scale = 1.0f;

    position_component[object->object_id].object_id = ascii_character;    // keep track of all position components
    object[ascii_character].component[COMP_POSITION] = object_position;   // add position component to object

    ////////////////////////// Model Component ///////////////////////////

    Game_Model *object_model;

    object_model = Load_Model_3D(   // memory is allocated by the model loader.
        file_path,
        color,
        &vao_storage,
        &vbo_storage
    );

    object_model->object_id = ascii_character;

    model_component[object->object_id].object_id = ascii_character;
    object[ascii_character].component[COMP_MODEL] = object_model;

    ///////////////////// Primary Characteristics Component ///////////////////////////////

    Primary_Characteristics* primary;

    primary = (Primary_Characteristics *) malloc(
        sizeof(Primary_Characteristics)
    );

    primary[ascii_character].object_id = ascii_character;

    primary->object_id = ascii_character;
    primary->strength = 9;
    primary->strength_cost = -10;
    primary->dexterity = 9;
    primary->dexterity_cost = -20;
    primary->intelligence = 9;
    primary->intelligence_cost = -20;
    primary->health = 9;
    primary->health_cost = -10;
    primary->health_status = HEALTH_STATUS_NONE;

    model_component[object->object_id].object_id = ascii_character;
    object[ascii_character].component[COMP_PRIMARY_CHARACTERISTICS] = primary;

    //////////////////// Secondary Characteristics Component ////////////////////////////////

    Secondary_Characteristics* secondary;

    secondary = (Secondary_Characteristics *) malloc(
        sizeof(Secondary_Characteristics)
    );

    secondary[ascii_character].object_id = ascii_character;

    secondary->object_id = ascii_character;
    secondary->hit_points_max = 9;
    secondary->hit_points_cost = 0;
    secondary->hit_points_current = 9;
    secondary->will = 9;
    secondary->perception = 9;
    secondary->fatigue_points = 9;
    secondary->basic_move = 4;
    secondary->base_speed = 4.25;
    secondary->action_current = ACTION_NONE;

    model_component[object->object_id].object_id = ascii_character;
    object[ascii_character].component[COMP_SECONDARY_CHARACTERISTICS] = secondary;

    //////////////////// Combat Stats Component ////////////////////////////////

    Combat_Stats* combat;

    combat = (Combat_Stats *) malloc(
        sizeof(Combat_Stats)
    );

    combat[ascii_character].object_id = ascii_character;

    combat->object_id = ascii_character;
    combat->thrust_damage = 1;
    combat->thrust_damage_modifier = -2;
    combat->swing_damage = 1;
    combat->swing_damage_modifier = -1;
    combat->damage_resistance = 1;
    combat->dodge = 7;
    combat->parry = 9;
    combat->block = 3;
    combat->shock = 0;

    model_component[object->object_id].object_id = ascii_character;
    object[ascii_character].component[COMP_COMBAT_STATS] = combat;

    ///////////////////////////////////////////////////////////////////////////////////
}

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
Name	        AC (v5)	AC
Leather	        3	    8
Ring mail	    4	    7
Studded leather	4	    7
Scale mail	    5   	6
Chain mail	    6   	5
Splint mail	    7   	4
Banded mail	    7   	4
Plate mail	    8   	3

A higher AC gives a better chance to avoid damage.

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
 * @ 10 )
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
 Rings @ 20
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
 Rods 000 /
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
    // TODO:(Frazor) add rods data
 /////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 Scrolls @ 000 ?
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
    // TODO: (Frazor) add Scroll data

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

void Game_Items_Cleanup()
{
    // TODO: (Frazor) ??? we already have a clean up function ???
}