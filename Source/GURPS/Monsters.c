//
// Created by frazor on 08/08/2020.
//

#include "Monsters.h"

static char* monster_levels =    "K BHISOR LCA NYTWFP GMXVJD ";
static char* monster_wandering = "KEBHISORZ CAQ YTW PUGM VJ  ";

const char* monsters_name[] = {
    "Player",
    "Aquator",
    "Bat",
    "Centaur",
    "Dragon",
    "Emu",
    "Venus Flytrap",
    "Griffin",
    "Hobgoblin",
    "Ice Monster",
    "Jabberwock",
    "Kobold",
    "Leprechaun",
    "Medusa",
    "Nymph",
    "Orc",
    "Phantom",
    "Quagga",
    "Rattlesnake",
    "Snake",
    "Troll",
    "Ur-Vile",
    "Vampire",
    "Wraith",
    "Xeroc",
    "Yeti",
    "Zombie",
};
static Health_Status health_status[27];
static u8 treasure[27] = {

    100, 0, 0 , 15, 100, 0, 0, 20, 0,     // percentage chance for monster to drop treasure
    0, 70, 0, 0, 40, 100, 15, 0, 0,
    0, 0, 50, 0, 20, 0, 30, 30, 0
};
typedef enum{

    MONSTERS_AI_NORMAL = 0,
    MONSTERS_AI_MEAN = 1,
    MONSTERS_AI_FLYING = 2,
    MONSTERS_AI_REGEN = 4,
    MONSTERS_AI_GREEDY = 8,
    MONSTERS_AI_INVISIBLE = 16

} Monsters_AI;

static u32 AI_to_use[27] = {

    MONSTERS_AI_NORMAL,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_FLYING,
    MONSTERS_AI_NORMAL,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_MEAN | MONSTERS_AI_FLYING | MONSTERS_AI_REGEN,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_NORMAL,
    MONSTERS_AI_NORMAL,
    MONSTERS_AI_MEAN | MONSTERS_AI_FLYING,
    MONSTERS_AI_NORMAL,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_NORMAL,
    MONSTERS_AI_GREEDY,
    MONSTERS_AI_INVISIBLE,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_REGEN | MONSTERS_AI_MEAN,
    MONSTERS_AI_MEAN,
    MONSTERS_AI_REGEN | MONSTERS_AI_MEAN,
    MONSTERS_AI_NORMAL,
    MONSTERS_AI_NORMAL,
    MONSTERS_AI_NORMAL,
    MONSTERS_AI_MEAN
    //u32 ** AI_to_use ** = mean, flying, regen, greedy, invisible, normal (flag 16+8+4+2+1+0 = 31 = 0x1F)
    // setup using an enum.
};
static u8 level[27] = {             // NOTE : only used for conversion from d&d.

    6, 5, 1, 4, 10, 1, 8, 13, 1,
    1, 15, 1, 3, 8, 3, 1, 8, 3,
    2, 1, 6, 7, 8, 5, 7, 4, 2
};

static i32 will[27];
static float base_speed[27];
static i32 unit_xp[27] = {

    0, 20, 1, 17, 5000, 2, 80, 2000, 3,
    5, 3000, 1, 10, 200, 37, 5, 120, 15,
    9, 2, 120, 190, 350, 55, 100, 50, 6
};
static i32 hit_points_max[27];
static i32 hit_points_current[27];
static i32 damage_resistance[27] = {

    2, 6, 6, 4, 9, 2, 5, 6, 4,
    0, 3, 2, 1, 6, 0, 3, 5, 5,
    5, 4, 4, 10, 6, 4, 2, 3, 1
};
static i32 dodge[27];
static u8 attack_skill[27];
static Damage_Type special_attack[27] = {

    DAMAGE_NORMAL,  DAMAGE_RUST_ARMOR, DAMAGE_FLIES_RANDOMLY,
    DAMAGE_NORMAL, DAMAGE_FIRE_BREATH, DAMAGE_NORMAL,
    DAMAGE_IMMOBILIZE, DAMAGE_NORMAL, DAMAGE_NORMAL,
    DAMAGE_FREEZE, DAMAGE_NORMAL, DAMAGE_NORMAL,
    DAMAGE_STEAL_GOLD, DAMAGE_CONFUSION, DAMAGE_STEAL_MAGIC_ITEM,
    DAMAGE_NORMAL, DAMAGE_NORMAL, DAMAGE_NORMAL,
    DAMAGE_POISON_STRENGTH, DAMAGE_NORMAL, DAMAGE_NORMAL,
    DAMAGE_NORMAL, DAMAGE_DRAIN_MAX_HP, DAMAGE_DRAIN_HP,
    DAMAGE_MIMIC, DAMAGE_NORMAL, DAMAGE_NORMAL
};
static Damage_Type damage_type[27] = {

    DAMAGE_CRUSHING, DAMAGE_SMALL_PIERCING, DAMAGE_IMPALING,
    DAMAGE_IMPALING, DAMAGE_LARGE_PIERCING, DAMAGE_CRUSHING,
    DAMAGE_CRUSHING, DAMAGE_CRUSHING, DAMAGE_CRUSHING,
    DAMAGE_CRUSHING, DAMAGE_PIERCING, DAMAGE_CRUSHING,
    DAMAGE_CRUSHING, DAMAGE_CRUSHING, DAMAGE_CRUSHING,
    DAMAGE_PIERCING, DAMAGE_PIERCING, DAMAGE_CRUSHING,
    DAMAGE_CRUSHING, DAMAGE_PIERCING, DAMAGE_CRUSHING,
    DAMAGE_CRUSHING, DAMAGE_CRUSHING, DAMAGE_CRUSHING
};
static i8 damage_melee[27] = {

    -2, -6, -4, +1, +7, -4, -6, +2, +2,
    -6, +9, -2, -5, +5, -6, +2, +4, +2,
    +0, -3, +5, +6, +4, +0, +2, +3, +2
};
static i8 damage_ranged[27];
static i32 shock[27];



void Monsters_Initialize_Models(
        Vector *vao_storage,
        Vector *vbo_storage,
        Game_Model *model_component,
        Game_Object *object) {

    char buffer[126];

    vec4 color = {0.1f, 0.5f, 0.1f, 1.0f};

    for (u8 index = 64; index < 91; index++) {      //  Z = 90

        if (index == 65) {

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
    } // end of monster model loading.
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

void Monsters_Data_Initialize() {

    memset (health_status,0,90);
    memset (shock, 0, 90);

    for(u8 index = 64; index < 91; index++){

        //health_status[index] = HEALTH_STATUS_NONE;
        will[index] = 3 + level[index];
        base_speed[index] = 4.19 + (level[index] * 0.01); // may need to modify this
        hit_points_max[index] = level[index];             // number of dice to roll
        hit_points_current[index] = hit_points_max[index];
        dodge[index] = will[index];
        attack_skill[index] = will[index];
        damage_ranged[index] = level[index] - 6;
        //shock[index] = 0;
    }


}

/*
    // create each monsters components and stats.

     * Monsters
    List of Monsters (Original)
    Name	    Treasure	Flags	Exp	    HP	    AC	Damage	    Range	Notes
    Aquator	        0	    M	    20	    5d8	    2	0d0/0d0		        Rusts armor
    Bat	            0	    F	    1	    1d8	    3	1d2		            Flies randomly
    Centaur	        15        		17	    4d8	    4	1d2/1d5/1d5
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

     add to ecs COMP_MONSTER_STATS [26]
        Name[16]
        health_status
        u8 treasure
        bool ** AI_to_use ** = mean, flying, regen, greedy, invisible, normal (flag 16+8+4+2+1+0 = 31 = 0x1F)
        will
        base_speed
        XP
        HP
        damage_resistance
        dodge
        to-hit
        special_attack
        damage_type
        Damage
        Range
        combat_shock


        return component_data
    */

char Monsters_Add_To_Room(
    i8 dungeon_level){

    i8 danger;

    do {
        i8 randomness = Dice_Roll(1, 5) + Dice_Roll(1, 6);
        danger = dungeon_level + (randomness - 5);
        if (danger < 1) {
            danger = Dice_Roll(1, 6);
        }
        if (danger > 26) {
            danger = 22 + Dice_Roll(1,5);
        }
    } while(monster_levels[--danger] == ' ');

    return monster_levels[danger];
}

char Monsters_Add_Wandering(i8 dungeon_level){

    i8 danger;

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

const char* Monsters_Name(i32 monster_id) {
    return monsters_name[monster_id];
}

Health_Status Monsters_Health_Status(i32 monster_id) {
    return health_status[monster_id];
}

u8 Monsters_Treasure(i32 monster_id) {
    return treasure[monster_id];
}

u32 Monsters_AI_To_Use(i32 monster_id) {
    return AI_to_use[monster_id];
}

i32 Monsters_Will(i32 monster_id) {
    return will[monster_id];
}

float Monsters_Base_Speed(i32 monster_id) {
    return base_speed[monster_id];
}

i32 Monsters_Unit_Xp(i32 monster_id) {
    return unit_xp[monster_id];
}

i32 Monsters_Hit_Points_Max(i32 monster_id) {
    return hit_points_max[monster_id];
}

i32 Monsters_Hit_Points_Current(i32 monster_id) {
    return hit_points_current[monster_id];
}

i32 Monsters_Damage_Resistance(i32 monster_id) {
    return damage_resistance[monster_id];
}

i32 Monsters_Dodge(i32 monster_id) {
    return dodge[monster_id];
}

u8 Monsters_Attack_Skill(i32 monster_id) {
    return attack_skill[monster_id];
}

Damage_Type Monsters_Special_Attack(i32 monster_id) {
    return special_attack[monster_id];
}

Damage_Type Monsters_Damage_Type(i32 monster_id) {
    return damage_type[monster_id];
}

u8 Monsters_Damage_Melee(i32 monster_id) {
    return damage_melee[monster_id];
}

u8 Monsters_Damage_Ranged(i32 monster_id) {
    return damage_ranged[monster_id];
}

i32 Monsters_Shock(i32 monster_id) {
    return shock[monster_id];
}
