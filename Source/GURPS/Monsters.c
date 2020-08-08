//
// Created by frazor on 08/08/2020.
//

#include "Monsters.h"

static char* monster_levels =    "K BHISOR LCA NYTWFP GMXVJD";
static char* monster_wandering = "KEBHISORZ CAQ YTW PUGM VJ ";

void Monsters_Initialize_Models(
        Vector *vao_storage,
        Vector *vbo_storage,
        Game_Model *model_component,
        Game_Object *object){

    char buffer[126];
    i32 index = 64;
    vec4 color = { 0.1f, 0.5f, 0.1f, 1.0f };

    for(index = 64; index < 91; index++) {      //  Z = 90

        if(index == 65){

            color[0] = 0.5f;
            color[1] = 0.25f;
        }

        sprintf(
            buffer,
            "Resource/Models/Ascii_3D/%c.obj",
            index
        );

        Monsters_Load_Monster_Model(
            index,
            color,
            buffer,
            vao_storage,
            vbo_storage,
            model_component,
            object
            );
    } // end of model loading.

    // create each monsters components and stats.
    /*
     * Monsters
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

    Object_Add_Position(
        monster_id,
        room
    );

    // we need to enable different stats for each monster.
    Object_Add_Primary_Characteristics(
        monster_id
    );

    Object_Add_Secondary_Characteristics(
        monster_id
    );

    Object_Add_Combat_Stats(
        monster_id
    );
    */
}

void Monsters_Load_Monster_Model(
    i32 object_id,
    vec4 color,
    const char* file_path,
    Vector *vao_storage,
    Vector *vbo_storage,
    Game_Model *model_component,
    Game_Object *object) {


    Game_Model *object_model;

    object_model = Load_Model_3D(   // memory is allocated by the model loader.
        file_path,
        color,
        vao_storage,
        vbo_storage
    );

    object_model->object_id = object_id;

    model_component[object->object_id].object_id = object_id;
    object[object_id].component[COMP_MODEL] = object_model;
}

void Monsters_For_New_Level(
    i8 current_dungeon_level){

    //distribute monsters across the level.
/* how many ?
 * monsters_added = 0
 *
 * add a monster
 *
 * copy its stats to the monster list for the level (101)
     TODO : initialize a new dungeon level
    */
}

char Monsters_Add_Wandering(i8 dungeon_level){

    i8 danger = 0;

    do {
        i8 randomness = Dice_Roll(1, 5) + Dice_Roll(1, 6);
        danger = dungeon_level + (randomness - 5);
        if (danger < 1) {
            danger = Dice_Roll(1, 6);
        }
        if (danger > 26) {
            danger = 22 + Dice_Roll(1,5);
        }
    } while(monster_wandering[--danger] == ' ');

    return monster_wandering[danger];
}
