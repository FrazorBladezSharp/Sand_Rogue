//
// Created by frazor on 24/07/2020.
//

#ifndef SAND_ROGUE_COMMON_H
#define SAND_ROGUE_COMMON_H

/////////////////////// Dependency Includes ///////////////////////////

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

/////////////////// C Standard Lib Includes ////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <cglm/cglm.h>

//////////////////////////// Defines //////////////////////////////////

#define UNUSED -1

#define WINDOW_TITLE "Sand_Rogue V0.1"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 500

#define MAP_WIDTH 80
#define MAP_HEIGHT 40

#define MAX_ENTITIES 1024

////////////////////////// Typedefs ////////////////////////////////////

//typedef uint8_t		u8;
typedef uint32_t u32;
//typedef uint64_t	u64;
//typedef int8_t		i8;
typedef int32_t i32;
//typedef int64_t		i64;

///////////////////////////// Structs ////////////////////////////////

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
//    COMP_VISIBILITY,
//    COMP_SOLID_BODY,
//    COMP_MOVEMENT,

//    COMP_COUNT                                  // keep a count on how many components we have

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

///////////////////////////////////////////////////////////////

#endif //SAND_ROGUE_COMMON_H