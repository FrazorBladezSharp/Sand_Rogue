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

typedef struct {

    i8 dungeon_level;
    bool map_cells[MAP_WIDTH + 1][MAP_HEIGHT + 1];

} Dungeon_Level_Current;

typedef struct {
    vec3 position;
    float rotationX;
    float rotationY;
    float rotationZ;
    mat4 view_matrix;
} Main_Camera;

///////////////////////////// ECS /////////////////////////////////

typedef enum {
    COMP_POSITION = 0,
    COMP_MODEL,
    COMP_PRIMARY_CHARACTERISTICS,
    COMP_SECONDARY_CHARACTERISTICS,
    COMP_COMBAT_STATS,

    COMP_COUNT                                  // keep a count on how many components we have

} Game_Component;

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

typedef struct
{
    unsigned int object_id;
    GLuint vaoID;
    GLuint num_indices;
    mat4 model_matrix;

} Game_Model;

typedef struct{

    i32 strength;
    i32 strength_cost;
    i32 dexterity;
    i32 dexterity_cost;
    i32 intelligence;
    i32 intelligence_cost;
    i32 health;
    i32 health_cost;

} Primary_Stats;

//COMP_SECONDARY_STATS,
typedef struct{

    i32 hit_points;
    i32 will;
    i32 perception;
    i32 fatigue_points;
    i32 basic_speed;
    i32 basic_move;

} Secondary_Stats;

// combat stats
typedef struct{

    i32 damage_resistance;
    i32 dodge;
    i32 parry;
    i32 block;

} Combat_Stats;

///////////////////// Game State ///////////////////////////////

typedef enum{

    ACTION_NONE,
    ACTION_MOVE,
    ACTION_ATTACK,

    ACTION_COUNT

} Action;

typedef  struct {

    // running
    bool game_is_running;
    // camera
    Main_Camera main_camera;
    // player_position
    Position* players_current_position;
    Action players_current_action;

} Current_Game_State;

#endif //SAND_ROGUE_COMMON_H
