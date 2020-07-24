
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


/* assimp include files. These three are usually needed. */
//#include <assimp/cimport.h>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

#include "Source/Common.h"
#include "Source/Core/Text_File_Utils.h"
#include "Source/OpenGL/Shaders.h"
#include "Source/Sand_Maths/Matrix_Utils.h"

////////////////////// Global Variables /////////////////////////////

//mat4 projection_matrix;
bool g_map_cells[MAP_WIDTH][MAP_HEIGHT];
Position g_position_component[MAX_ENTITIES];

/////////////////////////////////////////////////////////////////////
int
/// The run time entry point for Sand_Rogue
/// \return 0 = all ok.
main() {
    printf(
        "Welcome to Sand_Rogue !\n\n"
    );

    for (u32 x = 0; x < MAP_WIDTH; x++) {                     // create an empty map
        for (u32 y = 0; y < MAP_HEIGHT; y++) {
            g_map_cells[x][y] = false;                      // false = wall : true = floor tile
        }
    }


    Game_Entities game_entities;
    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize Entities
        game_entities.entity_id[index] = UNUSED;            // set all entities to unused
    }

    Game_Object player;

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // find an unused entity slot
        if (game_entities.entity_id[index] == UNUSED) {       // initialize player
            game_entities.entity_id[index] = index;         // register player as an entity
            player.object_id = index;                      // assign the player an entity id
            break;
        }
    }


    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize position component
        g_position_component[index].object_id = UNUSED;
    }

    Position *player_position;

    // NOTE: you must free the memory before game exit      *** NOTE ****

    player_position = (Position *) malloc(
        sizeof(Position)
    );

    player_position->object_id = player.object_id;         // set values for the player position.
    player_position->position[0] = 0.0f;                    // initialize all to zero
    player_position->position[1] = 0.0f;
    player_position->position[2] = 0.0f;
    player_position->rotationX = 0.0f;
    player_position->rotationY = 0.0f;
    player_position->rotationZ = 0.0f;
    player_position->scale = 0.1f;                          // assimp scales up all loaded models

    player.component[COMP_POSITION] = player_position;     // add position component to player


    g_position_component[player.object_id].object_id =     // keep track of all position components
        player.object_id;

    /////////////////////////////////////////////////////////////////

    // create Dungeon Level - can be done anytime before main game loop






    // window openGL - NOTE : must be done first to get the openGL context.

    SDL_Window *window;                                   // Declare a pointer

    SDL_Init(SDL_INIT_EVERYTHING);                   // Initialize SDL2

    window = SDL_CreateWindow(
        WINDOW_TITLE,                                 // window title
        1000,                                      // initial x position
        250,                                       // initial y position
        WINDOW_WIDTH,                                 // width, in pixels
        WINDOW_HEIGHT,                                // height, in pixels
        SDL_WINDOW_OPENGL                        // flags
    );

    ////////////// initializing OpenGL 3.3 ///////////////

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION,
        3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION,           // set the OpenGL version
        3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    SDL_GLContext gfx;

    gfx = SDL_GL_CreateContext(                         // create our windows OpenGL context
        window
    );

    if (gfx == NULL) {

        printf(
            "OpenGL context could not be created!"
        );

        return 1;
    }

    if (glewInit() != GLEW_OK) {                          // generate the OpenGL functions

        printf(
            "failed to initialize openGL (GLEW)."
        );

        return 1;
    }

    SDL_GL_SetSwapInterval(
        1                                    // 1 = vsync
    );

    printf(
        "OpenGL Version : %s\n",
        glGetString(GL_VERSION)
    );

    glClearColor(                                    // the window background color
        0.10f,
        0.07f,
        0.04f,
        1.0f
    );

    glEnable(
        GL_DEPTH_TEST
    );

    //////////////////// create a Triangle /////////////////////////
    // floor tile - start with a triangle and build up from there

    GLfloat vertex_array[] = {
        -0.5f, 0.0f, -0.5f, // v0 far left
        -0.5f, 0.0f, 0.5f, // v1 near left
        0.5f, 0.0f, 0.5f, // v2 near right
        0.5f, 0.0f, -0.5f  // v3 far right
    };

    GLfloat color_array[] = {
        0.5f, 0.1f, 0.5f, 1.0f,
        0.4f, 0.4f, 0.4f, 1.0f,
        0.5f, 0.1f, 0.5f, 1.0f,
        0.4f, 0.4f, 0.4f, 1.0f
    };

    GLuint index_array[] = {
        0, 1, 2,             // triangle 0
        0, 2, 3              // triangle 1
    };

    GLuint vaoID;

    glCreateVertexArrays(
        1,
        &vaoID
    );

    glBindVertexArray(                          // bind the VAO to record what we do
        vaoID
    );

    /////////////////////////// Index Buffer ////////////////////////////////////

    u32 iboID;                              // Index Buffer Object for our Indices

    glGenBuffers(
        1,
        &iboID
    );

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        iboID
    );

    glBufferData(                           // send our data to the Gfx Card
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(index_array) * sizeof(GLuint),
        &index_array[0],
        GL_STATIC_DRAW
    );


    /////////////////////////////// Vertex Buffer ///////////////////////////////////////////////

    GLuint vboID;                                  // Vertex Buffer Object for the vertices

    glGenBuffers(
        1,
        &vboID
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        vboID
    );

    glBufferData(                               // send our data to the gfx card
        GL_ARRAY_BUFFER,
        sizeof(vertex_array) * sizeof(GLfloat),
        &vertex_array[0],
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,                  // attribute must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,                  // stride
        (void *) 0            // array buffer offset
    );

    glEnableVertexAttribArray(
        0
    );

    /////////////////////////// Color Buffer /////////////////////////////////////////

    GLuint color_buffer;                                  // Vertex Buffer Object for the vertices

    glGenBuffers(
        1,
        &color_buffer
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        color_buffer
    );

    glBufferData(                               // send our data to the gfx card
        GL_ARRAY_BUFFER,
        sizeof(color_array) * sizeof(GLfloat),
        &color_array[0],
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        1,                  // attribute must match the layout in the shader.
        4,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,                  // stride
        (void *) 0            // array buffer offset
    );

    glEnableVertexAttribArray(
        1
    );

    //////////////////// create the floor Model //////////////////////////

    Game_Model floor = {
        .vaoID = vaoID,
        .num_indices = sizeof(index_array),
        .object_id = UNUSED,
    };

    /////////////////// Unbind the buffers ////////////////////


    glBindVertexArray(                      // disable our VAO
        0
    );

    glBindBuffer(                           // disable our VBO
        GL_ELEMENT_ARRAY_BUFFER,
        0
    );

    glBindBuffer(                           // disable oud IBO
        GL_ARRAY_BUFFER,
        0
    );

    //////////////////// Shader /////////////////////////////////

    GLint shader = Load_Shader();
    glUseProgram(shader);

    /////////////////// Matrix locations in Shader ////////////////

    GLint model_matrix_loc = glGetUniformLocation(shader, "model_matrix");
    GLint view_matrix_loc = glGetUniformLocation(shader, "view_matrix");
    GLint projection_matrix_loc = glGetUniformLocation(shader, "projection_matrix");

    /////////////////////////////////////////////////////////////

    // player model component

    // camera
    Main_Camera camera;

    camera.position[1] = 2.0f;
    camera.position[2] = 2.0f;
    camera.rotationX = 45.0f;

    camera = Calc_Camera_View_Matrix(camera) ;

    mat4 projection_matrix;

    glm_perspective(
        45.0f,
        9.0f / 5.0f,
        0.1,
        50.0f,
        projection_matrix
    );

    // main run time game loop
    bool running = true;
    SDL_Event event;

    while (running) {

        while (SDL_PollEvent(&event) == SDL_TRUE) {

            if (event.type == SDL_QUIT) {

                running = false;

            }

        } // end of Poll event loop

        // game input

        // game update

        // render

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        ///////////////// Render ////////////////////////////////

        glUseProgram(
            shader
        );

        glBindVertexArray(                          // set which VAO to draw
            floor.vaoID
        );

        glUniformMatrix4fv(
            projection_matrix_loc,
            1,
            GL_FALSE,
            (float *)projection_matrix
        );

        glUniformMatrix4fv(
            view_matrix_loc,
            1,
            GL_FALSE,
            (float *)camera.view_matrix
        );

        vec3 floor_position = {0.0f, 0.0f, -1.0f};
        vec3 scale = {1.0f, 1.0f, 1.0f};
        floor = Calc_Model_matrix(
            floor,
            floor_position,
            0.0f,
            0.0f,
            0.0f,
            scale
        );

        glUniformMatrix4fv(
            model_matrix_loc,
            1,
            GL_FALSE,
            (float *)floor.model_matrix
        );

        glDrawElements(                               // draw using Triangles
            GL_TRIANGLES,
            sizeof(index_array),
            GL_UNSIGNED_INT,
            (void *) 0
        );

        glBindVertexArray(                          // disable the used VAO
            0
        );

        //////////////////////////////////////////////////////////
        // swap buffers for OpenGL
        SDL_GL_SwapWindow(
            window
        );

        SDL_Delay(                                 // give the cpu a well earned break !
            10
        );

    }// end of the main game loop

    // player movement
    // camera movement for debug
    // rendering functionality

    ///////////////////////////////////////////////////////////////

    // free up resources
    free(
        player.component[COMP_POSITION]
    );

    SDL_DestroyWindow(
        window
    );

    SDL_Quit();

    return 0;
}
