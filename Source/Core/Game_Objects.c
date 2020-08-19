//
// Created by frazor on 29/07/2020.
//
//! \brief the player is expected to earn 0-5 character points per level
//  with a bonus for completing a set number of levels.
//  so set 5 objectives per level

#define MAX_ITEMS 1024
#include "Game_Objects.h"

static Vector vao_storage;
static Vector vbo_storage;
static Vector monsters_wandering;   // initialize to ACTION_NONE
static Vector monsters_rooms;       // initialize to ACTION_ASLEEP

static const char* game_items[MAX_ITEMS];              // Item data used for generating Objects
static i32 game_item_value[MAX_ITEMS];
static i32 game_armor_rating[9];
static i32 game_weapon_damage_modifier[9];
static bool game_weapon_damage[9];
static Damage_Type game_weapon_damage_type[9];

static Game_Object object[MAX_ENTITIES];
static Game_Entities game_entities[MAX_ENTITIES];
static Position position_component[MAX_ENTITIES];
static Game_Model model_component[MAX_ENTITIES];
static Primary_Characteristics primary_characteristic_component[MAX_ENTITIES];
static Secondary_Characteristics secondary_characteristic_component[MAX_ENTITIES];
static Combat_Stats combat_stats_component[MAX_ENTITIES];
static Monster_Stats monster_stats_component[MAX_ENTITIES];
//static Room_Contents room_contents[MAX_ROOM_CONTENTS];

void Object_Initialize() {
    Vector_Init(
        &vao_storage                // initialize OpenGL handle storage
    );

    Vector_Init(
        &vbo_storage                // used to delete Gfx Card buffers
    );

    Vector_Init(&monsters_wandering);
    Vector_Init(&monsters_rooms);

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize Entities

        game_entities->entity_id[index] = UNUSED;            // set all entities to unused
        object[index].object_id = UNUSED;                    // set all objects to unused
    }

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize components

        position_component[index].object_id = UNUSED;       // clear all component id's
        model_component[index].object_id = UNUSED;
        primary_characteristic_component[index].object_id = UNUSED;
        secondary_characteristic_component[index].object_id = UNUSED;
        combat_stats_component[index].object_id = UNUSED;
        monster_stats_component[index].object_id = UNUSED;
    }

    Monsters_Initialize_Models(
        &vao_storage,
        &vbo_storage,
        &model_component[0],
        &object[0]
    );

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
    Monsters_Data_Initialize();

    for (u8 index = 64; index < 91; index++) {

        Object_Add_Monster_Stats(
            index
        );
    }

    Items_Initialize_Models(
        &vao_storage,
        &vbo_storage,
        &model_component[0],
        &object[0]
    );

    // for each room test for a wandering monster
    i32 number_of_rooms = Map_Number_Of_Rooms();
    Dungeon_Level_Current *current_level = Dungeon_level();
    i8 level = current_level->dungeon_level;

    for (i32 monster_room = 0; monster_room < number_of_rooms; monster_room++) {

        i32 dice_roll = Dice_Roll(1, 6);

        printf("Wandering Monster dice roll = %d \n", dice_roll);

        if (dice_roll == 1) {

            char monster_model = Monsters_Add_Wandering(level);
            i32 index;

            for (index = 300; index < MAX_ENTITIES; index++) {      // initialize Entities

                if (object[index].object_id == UNUSED) {

                    break;
                }            // set new monster index
            }
            //static Game_Object object[MAX_ENTITIES];
            object[index].object_id = (i32) monster_model;
            //static Game_Entities game_entities[MAX_ENTITIES];
            game_entities->entity_id[index] = (i32) monster_model;
            //static Position position_component[MAX_ENTITIES];
            // we need to create a position
            Position *monster_position = (Position *) malloc(sizeof(Position));
            monster_position = Dungeon_Place_Monster(monster_room, monster_position);
            monster_position->rotationX = 0.0f;
            monster_position->rotationY = -45.0f;
            monster_position->rotationZ = 0.0f;
            monster_position->scale = 1.0f;
            monster_position->object_id = index;

            position_component[object->object_id].object_id = index;    // keep track of all position components
            object[index].component[COMP_POSITION] = monster_position;   // add position component to object

            // as above but with the model

            Game_Model *object_model;

            object_model = (Game_Model *) malloc(
                sizeof(Game_Model)
            );

            Game_Model *model_to_use = (Game_Model *) Object_Lookup_Component((i32) monster_model, COMP_MODEL);

            object_model->object_id = model_to_use->object_id;
            object_model->vaoID = model_to_use->vaoID;
            object_model->num_indices = model_to_use->num_indices;

            model_component[object->object_id].object_id = index;
            object[index].component[COMP_MODEL] = object_model;

            // TODO : make solid and add combat stats + set current HP set to AI_MEAN ACTION_NONE

            Vector_Append(&monsters_wandering, index);
        }
    } // end of wandering monsters

    Game_Item_Data_Initialize();            // Initialize the data so we can make objects
    // TODO : add Items model position and item stats
    // populate room 0 with possible items
    i32 dice_roll = Dice_Roll(1, 6);
    printf("Room Item dice roll = %d \n", dice_roll);
    while(dice_roll <= 2){

        // item category          dont forget food and gold
        // 1 d 100 for an item from that category

        // once we know which item, create and place the object.

        dice_roll = Dice_Roll(1, 6);
    }

    // populate room 0 with possible residents
    dice_roll = Dice_Roll(1, 6);

    printf("Room Monster dice roll = %d \n", dice_roll);

    if (dice_roll <= 2) {

        char monster_model = Monsters_Add_Wandering(level);
        i32 index;

        for (index = 400; index < MAX_ENTITIES; index++) {      // initialize Entities

            if (object[index].object_id == UNUSED) {

                break;
            }            // set new monster index
        }
        //static Game_Object object[MAX_ENTITIES];
        object[index].object_id = (i32) monster_model;
        //static Game_Entities game_entities[MAX_ENTITIES];
        game_entities->entity_id[index] = (i32) monster_model;
        //static Position position_component[MAX_ENTITIES];
        // we need to create a position
        Position *monster_position = (Position *) malloc(sizeof(Position));
        monster_position = Dungeon_Place_Monster(0, monster_position);
        monster_position->rotationX = 0.0f;
        monster_position->rotationY = -45.0f;
        monster_position->rotationZ = 0.0f;
        monster_position->scale = 1.0f;
        monster_position->object_id = index;

        position_component[object->object_id].object_id = index;    // keep track of all position components
        object[index].component[COMP_POSITION] = monster_position;   // add position component to object

        // as above but with the model

        Game_Model *object_model;

        object_model = (Game_Model *) malloc(
            sizeof(Game_Model)
        );

        Game_Model *model_to_use = (Game_Model *) Object_Lookup_Component((i32) monster_model, COMP_MODEL);

        object_model->object_id = model_to_use->object_id;
        object_model->vaoID = model_to_use->vaoID;
        object_model->num_indices = model_to_use->num_indices;

        model_component[object->object_id].object_id = index;
        object[index].component[COMP_MODEL] = object_model;

        // TODO : TODO : make solid and add combat stats + set current HP set to ACTION_SLEEP

    }
    // TODO : add Items model position and item stats

    // populate room 0 with possible items


    // we have discovered room 0 by default
    Dungeon_Level_Rooms* level_rooms = Map_Lookup_Room(0);
    level_rooms->discovered = true;
}

i32 Object_Create(
        i32 index,
        i32 ascii_character) {

    game_entities->entity_id[index] = ascii_character;         // register object as an entity
    object[index].object_id = ascii_character;                 // assign the object an entity id

    return index;
}

Current_Game_State Object_Add_Room_Monster_To_Render(
    Current_Game_State render_objects){

    for(i32 monster_id = 400; monster_id < MAX_ENTITIES; monster_id++){

        if(object[monster_id].object_id == UNUSED){

            return render_objects;
        }

        Vector_Append(&render_objects.models_to_render, monster_id);
        printf("Wandering Monster added to Rendering : %d\n", monster_id);
    }

    return render_objects;

}

Current_Game_State  Object_Add_Wandering_Monster_To_Render(
    Current_Game_State render_objects){

    for(i32 monster_id = 300; monster_id < MAX_ENTITIES; monster_id++){

        if(object[monster_id].object_id == UNUSED){

            return render_objects;
        }

        Vector_Append(&render_objects.models_to_render, monster_id);
        printf("Wandering Monster added to Rendering : %d\n", monster_id);
    }

    return render_objects;
}

Current_Game_State  Object_Add_Monster_To_Render(
    Current_Game_State render_objects){

    i32 monster_id = 77;
    i32 room = 0;

    Object_Add_Position(monster_id, room);

    Vector_Append(&render_objects.models_to_render, monster_id);
    return render_objects;
}

Current_Game_State Object_Add_Doors_To_Render(
    Current_Game_State render_objects){

    // ask Items for a list of doors Vector ?
    i32 door = 43;

    Dungeon_Level_Current* current = Items_Add_Fixtures_To_Level();

    for(i32 x = 0; x < MAP_WIDTH; x++){

        for(i32 z = 0; z < MAP_HEIGHT; z++){

            if(current->map_fixtures[x][z] == door){

                printf("current->map_fixtures[%d][%d]\n", x, z);

                u32 index;

                for (index = 100; index < MAX_ENTITIES; index++) {      // initialize Entities

                    if(object[index].object_id  == UNUSED){

                        break;
                    }            // set new door index
                }
                printf("New Object created : %d\n", index);
                printf("Position = x : %d, z : %d\n", x, z);

                game_entities->entity_id[index] = index;
                object[index].object_id = index;

                // add position of door
                Position *object_position;

                object_position = (Position *) malloc(
                    sizeof(Position)
                );

                object_position->object_id = index;

                object_position->position[0] = (float) x;
                object_position->position[1] = 0.5f;
                object_position->position[2] = (float) z;
                object_position->rotationX = 0.0f;
                object_position->rotationY = -45.0f;
                object_position->rotationZ = 0.0f;
                object_position->scale = 1.0f;

                position_component[object->object_id].object_id = index;    // keep track of all position components
                object[index].component[COMP_POSITION] = object_position;   // add position component to object

                ////////////////// add model ///////////////////////////////////////////

                Game_Model* object_model;

                object_model = (Game_Model *) malloc(
                    sizeof(Game_Model)
                );

                Game_Model* model_to_use = (Game_Model*)Object_Lookup_Component(door, COMP_MODEL);

                object_model->object_id = model_to_use->object_id;
                object_model->vaoID = model_to_use->vaoID;
                object_model->num_indices = model_to_use->num_indices;

                model_component[object->object_id].object_id = index;
                object[index].component[COMP_MODEL] = object_model;

                Vector_Append(&render_objects.models_to_render, index);
            } // end of if model = 42
        } // end of z loop
    } // end of x loop

    return render_objects;
}

Current_Game_State Object_Add_Stairs_To_Render(Current_Game_State render_objects)
{
    i32 id = 62;
    i32 room = 0;

    Object_Add_Position(id, room);

    Vector_Append(&render_objects.models_to_render, id);
    return render_objects;
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
            sizeof(Combat_Stats) + 4
        );

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

    i32 monster_id = object_id - 64;

    monster->object_id = object_id;
    sprintf(monster->name,"%s", Monsters_Name(monster_id));
    monster->health_status = Monsters_Health_Status(monster_id);
    monster->treasure = Monsters_Treasure(monster_id);
    monster->AI_to_use = Monsters_AI_To_Use(monster_id);
    monster->will = Monsters_Will(monster_id);
    monster->base_speed = Monsters_Base_Speed(monster_id);
    monster->unit_xp = Monsters_Unit_Xp(monster_id);
    monster->hit_points_max = Monsters_Hit_Points_Max(monster_id);
    monster->hit_points_current = Monsters_Hit_Points_Current(monster_id);
    monster->damage_resistance = Monsters_Damage_Resistance(monster_id);
    monster->dodge = Monsters_Dodge(monster_id);
    monster->attack_skill = Monsters_Attack_Skill(monster_id);
    monster->special_attack = Monsters_Special_Attack(monster_id);
    monster->damage_type = Monsters_Damage_Type(monster_id);
    monster->damage_melee = Monsters_Damage_Melee(monster_id);
    monster->damage_ranged = Monsters_Damage_Ranged(monster_id);
    monster->shock = Monsters_Shock(monster_id);
    monster->health = Monster_Health(monster_id);
    monster->attack_target = Monster_Attack_Target(monster_id);

    monster_stats_component[object->object_id].object_id = object_id;
    object[object_id].component[COMP_MONSTER_STATS] = monster;
}

//////////////////////////////////////////////////////////////////////

i32  Object_lookup_Wandering_Monster_location(i32 x_axis, i32 z_axis)
{
    i32 target_id = 0;

    for(i32 index = 0; index < Vector_Size(&monsters_wandering); index++){

        i32 current_id = Vector_Get(&monsters_wandering, index);

        Position* monster = (Position*)Object_Lookup_Component(
            current_id,
            COMP_POSITION
        );

        if(monster->position[0] == x_axis && monster->position[2] == z_axis){

            target_id = current_id;
            break;
        }
    }

    return target_id;
}
i32  Object_lookup_Room_Monster_location(i32 x_axis, i32 z_axis)
{
    i32 target_id = 0;

    for(i32 index = 0; index < Vector_Size(&monsters_rooms); index++){

        i32 current_id = Vector_Get(&monsters_rooms, index);

        Position* monster = (Position*)Object_Lookup_Component(
            current_id,
            COMP_POSITION
        );

        if(monster->position[0] == x_axis && monster->position[2] == z_axis){

            target_id = current_id;
            break;
        }
    }

    return target_id;
}

void* Object_Lookup_Component(
    i32 object_id,
    i32 component)
{
    return object[object_id].component[component];
}

void Object_Cleanup()
{
    // delete all vbo's that have been created
    printf(
        "Deleting VBO vectors: %d\n",
        Vector_Size(&vbo_storage)
    );

    for (int index = 0; index < Vector_Size(&vbo_storage); index++) {

        GLuint vbo = Vector_Get(
            &vbo_storage,
            index
        );

        glDeleteVertexArrays(
            1,
            (GLuint *) &vbo
        );
    }
    // delete all vao's that have been created
    printf(
        "Deleting VAO vectors: %d\n",
        Vector_Size(&vao_storage)
    );

    for (int index = 0; index < Vector_Size(&vao_storage); index++) {

        GLuint vao = Vector_Get(
            &vao_storage,
            index
        );

        glDeleteVertexArrays(
            1,
            (GLuint *) &vao
        );
    }

    Vector_Free_Memory(
        &vbo_storage
    );

    Vector_Free_Memory(
        &vao_storage
    );
}

/////////////////////////////////////////// Item Data /////////////////////////////////////

void Game_Item_Data_Initialize() {
/*
 * convert to G.U.R.P.S.
 * AC = AC - 2 first column works for our system
Armor @ 0 ]
Name	        AC (v5)	AC  %Drop
None            0       10  0
Leather	        3	    8   20 = 20
Ring mail	    4	    7   35 = 15
Studded leather	4	    7   50 = 15
Scale mail	    5   	6   63 = 13
Chain mail	    6   	5   75 = 12
Splint mail	    7   	4   85 = 10
Banded mail	    7   	4   95 = 10
Plate mail	    8   	3   100 = 5

A higher AC gives a better chance to avoid damage.
Older versions of Rogue used the decreasing AC to represent better armor (also shown in the table).
*/
    game_items[0] = "None";
    game_item_value[0] = 0;
    game_armor_rating[0] = 0;

    game_items[1] = "Light Leather Clothing";
    game_item_value[1] = 20;
    game_armor_rating[1] = 1;

    game_items[2] = "Ring Mail Armour";
    game_item_value[2] = 15;
    game_armor_rating[2] = 2;

    game_items[3] = "Studded Leather Armour";
    game_item_value[3] = 15;
    game_armor_rating[3] = 2;

    game_items[4] = "Scale Mail Armour";
    game_item_value[4] = 13;
    game_armor_rating[4] = 3;

    game_items[5] = "Chain Mail Armour";
    game_item_value[5] = 12;
    game_armor_rating[5] = 4;

    game_items[6] = "Splint Mail Armour";
    game_item_value[6] = 10;
    game_armor_rating[6] = 5;

    game_items[7] = "Banded Mail Armour";
    game_item_value[7] = 10;
    game_armor_rating[7] = 5;

    game_items[8] = "Plate Mail Armour";
    game_item_value[8] = 5;
    game_armor_rating[8] = 6;

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
    game_item_value[10] = 10;
    game_weapon_damage_modifier[0] = 3;
    game_weapon_damage[0] = false;
    game_weapon_damage_type[0] = DAMAGE_CRUSHING;

    game_items[11] = "Long Sword";
    game_item_value[11] = 10;
    game_weapon_damage_modifier[1] = 1;
    game_weapon_damage[1] = false;
    game_weapon_damage_type[0] = DAMAGE_CUTTING;

    game_items[12] = "Short Bow";
    game_item_value[12] = 10;
    game_weapon_damage_modifier[2] = -4;
    game_weapon_damage[2] = false;
    game_weapon_damage_type[0] = DAMAGE_CRUSHING;

    game_items[13] = "Arrow";
    game_item_value[13] = 10;
    game_weapon_damage_modifier[3] = 0;
    game_weapon_damage[3] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

    game_items[14] = "Dagger";
    game_item_value[14] = 10;
    game_weapon_damage_modifier[4] = 0;
    game_weapon_damage[4] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

    game_items[15] = "Two Handed Sword";
    game_item_value[15] = 10;
    game_weapon_damage_modifier[5] = 4;
    game_weapon_damage[5] = false;
    game_weapon_damage_type[0] = DAMAGE_CUTTING;

    game_items[16] = "Dart";
    game_item_value[16] = 10;
    game_weapon_damage_modifier[6] = -3;
    game_weapon_damage[6] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

    game_items[17] = "Shuriken";
    game_item_value[17] = 10;
    game_weapon_damage_modifier[7] = 2;
    game_weapon_damage[7] = true;
    game_weapon_damage_type[0] = DAMAGE_IMPALING;

    game_items[18] = "Spear";
    game_item_value[18] = 10;
    game_weapon_damage_modifier[8] = 3;
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
}
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
