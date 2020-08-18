//
// Created by frazor on 24/07/2020.
//

#ifndef SAND_ROGUE_COMMON_H
#define SAND_ROGUE_COMMON_H

/////////////////////// Dependency Includes ///////////////////////////

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
/* assimp include files. These three are usually needed. */
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/////////////////// C Standard Lib Includes ////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <cglm/cglm.h>

//////////////////////////// Defines //////////////////////////////////

#define UNUSED -1

#define WINDOW_TITLE "Sand_Rogue V0.1"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 500

#define MAP_WIDTH 80
#define MAP_HEIGHT 40
#define MAX_ROOM_WIDTH 16
#define MAX_ROOM_HEIGHT 12
//#define MAX_ROOMS 126
//#define MAX_ROOM_CONTENTS 1024 TODO : room contents

#define MAX_ENTITIES 1024

#define VECTOR_INITIAL_CAPACITY 8

////////////////////////// Typedefs ////////////////////////////////////

typedef uint8_t		u8;
typedef uint32_t    u32;
//typedef uint64_t	u64;
typedef int8_t		i8;
typedef int32_t     i32;
//typedef int64_    i64;

///////////////////////////// Structs ////////////////////////////////

typedef struct {

    i32 size;
    i32 capacity;
    i32 *data;

} Vector;

typedef struct {

    u8 x;
    u8 y;
    u8 z;

} Point_3D;

typedef enum {

    UNIFORM_LOC_MODEL_MATRIX = 0,
    UNIFORM_LOC_VIEW_MATRIX,
    UNIFORM_LOC_PROJECTION_MATRIX,
    UNIFORM_LOC_LIGHT_POSITION,
    UNIFORM_LOC_LIGHT_COLOR,
    UNIFORM_LOC_SHINE_DAMPER,
    UNIFORM_LOC_REFLECTIVITY,
    UNIFORM_LOC_SKY_COLOR,
    UNIFORM_LOC_CAMERA_POSITION

    //UNIFORM_LOC_COUNT

} Shader_Uniform_Locations;

typedef struct{

    GLuint shader_program;
    GLuint uniform_Locations[64];
} Shader;

typedef struct {

    i8 dungeon_level;
    bool map_cells[MAP_WIDTH + 1][MAP_HEIGHT + 1];
    i32 map_fixtures[MAP_WIDTH + 1][MAP_HEIGHT + 1];

} Dungeon_Level_Current;

typedef struct {

    i8 dungeon_level;
    bool discovered;
    u8 locationX;
    u8 locationY;
    u8 locationZ;
    u8 width;
    u8 breadth;
    u8 height;
    u8 light;
} Dungeon_Level_Rooms;

typedef struct {
    vec3 position;
    float rotationX;
    float rotationY;
    float rotationZ;
    mat4 view_matrix;
} Main_Camera;

///////////////////////////// ECS /////////////////////////////////

typedef enum {

    DAMAGE_NORMAL = 0,
    DAMAGE_SMALL_PIERCING,
    DAMAGE_PIERCING,
    DAMAGE_LARGE_PIERCING,
    DAMAGE_IMPALING,
    DAMAGE_CUTTING,
    DAMAGE_CRUSHING,
    DAMAGE_FIRE_BREATH,
    DAMAGE_FREEZE,
    DAMAGE_RUST_ARMOR,
    DAMAGE_FLIES_RANDOMLY,
    DAMAGE_IMMOBILIZE,
    DAMAGE_CONFUSION,
    DAMAGE_STEAL_GOLD,
    DAMAGE_STEAL_MAGIC_ITEM,
    DAMAGE_POISON_STRENGTH,
    DAMAGE_DRAIN_MAX_HP,
    DAMAGE_DRAIN_HP,
    DAMAGE_MIMIC

    //DAMAGE_TYPE_COUNT               // keep a count on how many Damage Types we have

} Damage_Type;

typedef enum{

    ACTION_NONE,
    ACTION_MOVE,
    ACTION_ATTACK,
    ACTION_RANGED_ATTACK,
    //ACTION_ASLEEP

    //ACTION_COUNT

} Action;

typedef enum{

    MONSTERS_AI_NORMAL = 0,
    MONSTERS_AI_MEAN = 1,
    MONSTERS_AI_FLYING = 2,
    MONSTERS_AI_REGEN = 4,
    MONSTERS_AI_GREEDY = 8,
    MONSTERS_AI_INVISIBLE = 16

} Monsters_AI;

typedef enum {
    COMP_POSITION = 0,
    COMP_MODEL,
    COMP_PRIMARY_CHARACTERISTICS,
    COMP_SECONDARY_CHARACTERISTICS,
    COMP_COMBAT_STATS,
    COMP_MONSTER_STATS

    //COMP_COUNT                                  // keep a count on how many components we have

} Game_Component;

typedef enum{

    HEALTH_STATUS_NONE = 0,
    HEALTH_STATUS_SHOCK,
    HEALTH_STATUS_MAJOR_WOUNDS,
    HEALTH_STATUS_KNOCKDOWN_AND_STUN,
    HEALTH_STATUS_UNCONCIOUS,
    HEALTH_STATUS_MORTAL_WOUNDS,
    HEALTH_STATUS_DEATH,
    HEALTH_STATUS_RESTED,
    HEALTH_STATUS_FULL_REST
    //HEALTH_STATUS_COUNT
} Health_Status;

typedef enum {

    ATTACK_TARGET_NONE = 0,
    ATTACK_TARGET_NORTH,
    ATTACK_TARGET_SOUTH,
    ATTACK_TARGET_WEST,
    ATTACK_TARGET_EAST

} Attack_Target;

typedef struct {
    i32 entity_id[MAX_ENTITIES];
} Game_Entities;

typedef struct {
    i32 object_id;
    void *component[64];
} Game_Object;

typedef struct {

    i32 object_id;
    vec3 position;
    float rotationX;
    float rotationY;
    float rotationZ;
    float scale;

} Position;

typedef struct{

    i32 object_id;
    GLuint vaoID;
    GLuint num_indices;
    mat4 model_matrix;

} Game_Model;

typedef struct{

    i32 object_id;
    i32 strength;
    i32 strength_cost;
    i32 dexterity;
    i32 dexterity_cost;
    i32 intelligence;
    i32 intelligence_cost;
    i32 health;
    i32 health_cost;
    Health_Status health_status;

} Primary_Characteristics;

typedef struct{

    i32 object_id;
    i32 hit_points_max;
    i32 hit_points_cost;
    i32 hit_points_current;
    i32 will;
    i32 perception;
    i32 fatigue_points;
    i32 basic_move;
    float base_speed;
    Action action_current;


} Secondary_Characteristics;

typedef struct {

    i32 object_id;
    i32 thrust_damage;
    i32 thrust_damage_modifier;
    i32 swing_damage;
    i32 swing_damage_modifier;
    i32 damage_resistance;
    i32 dodge;
    i32 parry;
    i32 block;
    i32 shock;

} Combat_Stats;

typedef struct {

    i32 object_id;
    char name[16];
    Health_Status health_status;
    u8 treasure;
    u32 AI_to_use;
    Attack_Target attack_target;
    i32 health;
    i32 will;
    i32 unit_xp;
    i32 hit_points_max;
    i32 hit_points_current;
    i32 damage_resistance;
    i32 dodge;
    u8 attack_skill;
    Damage_Type special_attack;
    Damage_Type damage_type;
    i8 damage_melee;
    i8 damage_ranged;
    i32 shock;
    float base_speed;

} Monster_Stats;

///////////////////// Game State ///////////////////////////////

typedef  struct {

    // running
    bool game_is_running;
    // camera
    Main_Camera main_camera;
    // player
    Action players_current_action;
    i32 number_of_rests;
    i32 natural_heal;
    bool is_player_in_a_room;
    i32 room_number;
    // models to render
    Vector models_to_render;

} Current_Game_State;

#endif //SAND_ROGUE_COMMON_H
