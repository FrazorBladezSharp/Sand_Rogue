
/*
###############################################################
# Project created by Frazor Sharp 2020 Jul 22
#
# Sand_Rogue for C / C++ Version 0.1
#
# Contact email         : frazor.sharp@virginmedia.com
# Github                : https://github.com/FrazorBladezSharp/Sand_Rogue
# Twitch                : FrazorBladezSharp
# Youtube               : Frazor Sharp
#
# All code is free to use as you please
# free for all Licence !
###############################################################
*/

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <cglm/cglm.h>
/* assimp include files. These three are usually needed. */
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

typedef uint8_t		u8;
typedef uint32_t	u32;
typedef uint64_t	u64;
typedef int8_t		i8;
typedef int32_t		i32;
typedef int64_t		i64;

//////////////////////////// Defines //////////////////////////////////

#define UNUSED -1

#define WINDOW_TITLE "Sand_Rogue V0.1"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 500

#define MAP_WIDTH 80
#define MAP_HEIGHT 40

#define MAX_ENTITIES 1024

///////////////////////////// Structs /////////////////////////////////

typedef struct {
    vec3 position;
    float rotationX;
    float rotationY;
    float rotationZ;
    mat4 view_matrix;
} Main_Camera;

typedef struct
{
    unsigned int object_id;
    GLuint vaoID;
    GLuint num_indices;
    mat4 model_matrix
} Floor_Tile;

typedef enum
{
    COMP_POSITION = 0,
    COMP_Model,
    COMP_VISIBILITY,
    COMP_SOLID_BODY,
    COMP_MOVEMENT,

    COMP_COUNT

}Game_Component;

typedef struct {
    i32 entity_id[MAX_ENTITIES];
} Game_Entities;

typedef struct {
    i32 object_id;
    void* component[64];
} Game_Object;

typedef struct
{
    i32 object_id;
    vec3 position;
    float rotationX;
    float rotationY;
    float rotationZ;
    float scale;
    mat4 model_matrix;
} Position;

typedef struct
{
    i32 object_id;
    GLuint vaoID;
    GLuint num_indices;
} Model;

////////////////////// Global Variables /////////////////////////////

mat4 projection_matrix;
bool g_map_cells[MAP_WIDTH][MAP_HEIGHT];
Position g_position_component[MAX_ENTITIES];

/////////////////////////////////////////////////////////////////////
int
/// The run time entry point for Sand_Rogue
/// \return 0 = all ok.
main() {
    printf("Welcome to Sand_Rogue !\n\n");

    // create an empty map
    for(u32 x = 0; x < MAP_WIDTH; x++){
        for(u32 y = 0; y < MAP_HEIGHT; y++){
            g_map_cells[x][y] = false;
        }
    }

    // initialize Entities and a player.
    Game_Entities game_entities;
    for(u32 index = 0; index < MAX_ENTITIES; index++){
        game_entities.entity_id[index] = UNUSED;
    }

    Game_Object *player;

    for(u32 index = 0; index < MAX_ENTITIES; index++){
        if(game_entities.entity_id[index] == UNUSED){
            game_entities.entity_id[index] = index;
            player->object_id = index;
            break;
        }
    }
    assert(player != NULL);

    // how are we going to treat our objects
    // ECS = Entity, Components, System.
    // camera is NOT an Entity.

    // initialize position component
    for(u32 index = 0; index < MAX_ENTITIES; index++){
        g_position_component[index].object_id = UNUSED;
    }
    // add position component to player
    Position  *player_position;
    // NOTE: you must free the memory before game exit
    player_position = (Position*)malloc(sizeof(Position));

    // set values for the player position.
    player_position->object_id = player->object_id;
    player_position->position[0] = 0.0f;
    player_position->position[1] = 0.0f;
    player_position->position[2] = 0.0f;
    player_position->rotationX = 0.0f;
    player_position->rotationY = 0.0f;
    player_position->rotationZ = 0.0f;
    player_position->scale = 0.1f;

    player->component[COMP_POSITION] = player_position;


    g_position_component[player->object_id].object_id = player->object_id;

    /////////////////////////////////////////////////////////////////

    // window openGL - must be done first to get the openGL context.

    // floor tile
    // create Dungeon Level
    // player model component
    // camera

    // main run time game loop
    // player movement
    // camera movement for debug
    // rendering functionality

    // free up resources
    free(player->component[COMP_POSITION]);

    return 0;
}


