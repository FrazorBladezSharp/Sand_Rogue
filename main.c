
/** @file Main
 * TODO: think about if statements as they can be taken out
 * eg a * ( condition for a ) + b * ( condition for b ) + etc ...
 *
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

#include "Source/Common.h"
#include "Source/Sand_Dice.h"
#include "Source/Core/Text_File_Utils.h"
#include "Source/OpenGL/Shaders.h"
#include "Source/Sand_Maths/Matrix_Utils.h"
#include "Source/Core/Game_Objects.h"
#include "Source/Core/Map.h"

int
/** The run time entry point for Sand_Rogue
 * @return 0 = all ok.
 */
main() {

    printf(
        "Welcome to Sand_Rogue !\n\n"
    );

    Object_Initialize();

    //////////////////////////////////////////////////////////////////////////
    // window openGL - NOTE : must be done first to get the openGL context.

    SDL_Window *window;                                   // Declare a pointer

    SDL_Init(SDL_INIT_EVERYTHING);                   // Initialize SDL2

    window = SDL_CreateWindow(
        WINDOW_TITLE,                                 // window title
        100,                                       // initial x position
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
        0.05f,
        0.02f,
        0.01f,
        1.0f
    );

    glEnable(
        GL_DEPTH_TEST
    );
        // TODO: (Frazor) enable Blending

    Game_Object player;
    player = Object_Create();

    //////////////////// create a Square /////////////////////////
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

    GLfloat normal_array[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
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

    Object_Add_VAO(vaoID);

    glBindVertexArray(                          // bind the VAO to record what we do
        vaoID
    );

    /////////////////////////// Index Buffer ////////////////////////////////////

    u32 iboID;                              // Index Buffer Object for our Indices

    glGenBuffers(
        1,
        &iboID
    );

    Object_Add_VBO(iboID);

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        iboID
    );

    glBufferData(                           // send our data to the Gfx Card
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(index_array),
        &index_array[0],
        GL_STATIC_DRAW
    );

    /////////////////////////////// Vertex Buffer ///////////////////////////////////////////////

    GLuint vboID;                                  // Vertex Buffer Object for the vertices

    glGenBuffers(
        1,
        &vboID
    );

    Object_Add_VBO(vboID);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        vboID
    );

    glBufferData(                               // send our data to the gfx card
        GL_ARRAY_BUFFER,
        sizeof(vertex_array),
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

    Object_Add_VBO(color_buffer);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        color_buffer
    );

    glBufferData(                               // send our data to the gfx card
        GL_ARRAY_BUFFER,
        sizeof(color_array),
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

    /////////////////////////// Normals Buffer /////////////////////////////////////////

    GLuint nboID;                                  // Vertex Buffer Object for the vertices

    glGenBuffers(
        1,
        &nboID
    );

    Object_Add_VBO(nboID);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        nboID
    );

    glBufferData(                               // send our data to the gfx card
        GL_ARRAY_BUFFER,
        sizeof(normal_array),
        &normal_array[0],
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        2,                  // attribute must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_TRUE,           // normalized
        0,                  // stride
        (void *) 0            // array buffer offset
    );

    glEnableVertexAttribArray(
        2
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

    ////////////////////////////////////// define the Player ////////////////////////////



    Position *player_position;
    //player_position = (Position *) malloc(sizeof(Position));
    Game_Model *player_model;
    //player_model = (Game_Model *) malloc(sizeof(Game_Model));

    player_position = player.component[COMP_POSITION];
    player_model = player.component[COMP_MODEL];

    //////////////////////////// Create a Dungeon Level///////////////////////////////

    Dice_Initialize();

    // create Dungeon Level - can be done anytime before main game loop
    i8 current_dungeon_level = 1;

    Dungeon_Level_Current *dungeon_level_current;

    dungeon_level_current = (Dungeon_Level_Current *) malloc(sizeof(Dungeon_Level_Current));

    dungeon_level_current->dungeon_level = current_dungeon_level;
    // set all locations to false.
    for (int x = 0; x <= MAP_WIDTH; x++) {
        for (int y = 0; y <= MAP_HEIGHT; y++) {
            dungeon_level_current->map_cells[x][y] = false;
        }
    }

    dungeon_level_current = Map_Create_Dungeon_Level(
        dungeon_level_current,
        player.component[COMP_POSITION]                     // we set player position as a side effect of the function
    );

    //////////////////// Shader /////////////////////////////////

    GLint shader = Load_Shader();
    glUseProgram(shader);

    /////////////////// Matrix locations in Shader ////////////////

    GLint model_matrix_loc = glGetUniformLocation(shader, "model_matrix");
    GLint view_matrix_loc = glGetUniformLocation(shader, "view_matrix");
    GLint projection_matrix_loc = glGetUniformLocation(shader, "projection_matrix");

    GLint light_position_loc = glGetUniformLocation(shader, "light_position");
    GLint light_color_loc = glGetUniformLocation(shader, "light_color");
    GLint shine_damper_loc = glGetUniformLocation(shader, "shine_damper");
    GLint reflectivity_loc = glGetUniformLocation(shader, "reflectivity");
    GLint sky_color_loc = glGetUniformLocation(shader, "sky_color");
    GLint camera_position_loc = glGetUniformLocation(shader, "camera_position");

    /////////////////////////////////////////////////////////////

    // camera
    Main_Camera camera;





    camera.position[0] = player_position->position[0] - 3.0f,
        camera.position[1] = 6.6f;
    camera.position[2] = player_position->position[2] + 3.0f;
    camera.rotationX = 60.0f;
    camera.rotationY = 45.0f;

    camera = Calc_Camera_View_Matrix(camera);

    mat4 projection_matrix;

    glm_perspective(
        45.0f,
        9.0f / 5.0f,
        0.1,
        50.0f,
        projection_matrix
    );

    vec3 light_position;

    light_position[0] = 39.0f; //player_position->position[0] + 40.0f;
    light_position[1] = 25.0f; //player_position->position[1] + 20.0f;
    light_position[2] = 20.0f; //player_position->position[2] + 20.0f;

    vec3 light_color;

    light_color[0] = 0.8f;
    light_color[1] = 0.8f;
    light_color[2] = 0.8f;

    // main run time game loop
    bool running = true;
    bool player_moves;

    SDL_Event event;
    i32 mouseX;
    i32 mouseY;

    while (running) {

        mouseX = 0;
        mouseY = 0;

        while (SDL_PollEvent(&event) == SDL_TRUE) {

            if (event.type == SDL_QUIT) {

                running = false;

            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                if (event.button.button == SDL_BUTTON_RIGHT) {

                    SDL_GetMouseState(
                        &mouseX,
                        &mouseY
                    );

                    player_moves = true;
                }
            }

        } // end of Poll event loop

        // (Frazor) camera movement for debug
        const u8 *currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
            running = false;
        }


        if (currentKeyStates[SDL_SCANCODE_W] &&
            currentKeyStates[SDL_SCANCODE_LSHIFT]) {

            camera.position[2] =
                camera.position[2] - 0.1f;

        } else if (currentKeyStates[SDL_SCANCODE_S] &&
                   currentKeyStates[SDL_SCANCODE_LSHIFT]) {

            camera.position[2] =
                camera.position[2] + 0.1f;
        }

        if (currentKeyStates[SDL_SCANCODE_A] &&
            currentKeyStates[SDL_SCANCODE_LSHIFT]) {

            camera.position[0] =
                camera.position[0] - 0.1f;

        } else if (currentKeyStates[SDL_SCANCODE_D] &&
                   currentKeyStates[SDL_SCANCODE_LSHIFT]) {

            camera.position[0] =
                camera.position[0] + 0.1f;
        }

        if (currentKeyStates[SDL_SCANCODE_Q] &&
            currentKeyStates[SDL_SCANCODE_LSHIFT]) {

            camera.position[1] =
                camera.position[1] - 0.1f;

        } else if (currentKeyStates[SDL_SCANCODE_E] &&
                   currentKeyStates[SDL_SCANCODE_LSHIFT]) {

            camera.position[1] =
                camera.position[1] + 0.1f;
        }

        camera = Calc_Camera_View_Matrix(camera);


    // TODO: (Frazor) player movement with wall detection.

    // Mouse R-click to move
    // get xy location of mouse
    // determine which of the 4 directions to move - 1 square
    // with community permission increase to 8 way.



        if ((((mouseX > WINDOW_WIDTH / 2 + 20) &&
            (mouseY < WINDOW_HEIGHT / 2 - 5) &&
            player_moves) ||
            currentKeyStates[SDL_SCANCODE_W]) &&
            dungeon_level_current->map_cells
            [(int)player_position->position[0] + 1]
            [(int)player_position->position[2]]) {

            // players x location increases by 1
            player_position->position[0] += 1;

            camera.position[0] =
                player_position->position[0] - 3.0f;

            player_moves = false;
        }

        if ((((mouseX > WINDOW_WIDTH / 2 + 20) &&
            (mouseY > WINDOW_HEIGHT / 2 + 5) &&
            player_moves) ||
            currentKeyStates[SDL_SCANCODE_D]) &&
            dungeon_level_current->map_cells
            [(int)player_position->position[0]]
            [(int)player_position->position[2] + 1]) {

            // player y location increases by 1
            player_position->position[2] += 1;

            camera.position[2] =
                player_position->position[2] + 3.0f;

            player_moves = false;
        }

        if ((((mouseX < WINDOW_WIDTH / 2 + 20) &&
            (mouseY > WINDOW_HEIGHT / 2 + 5) &&
            player_moves) ||
            currentKeyStates[SDL_SCANCODE_S]) &&
            dungeon_level_current->map_cells
            [(int)player_position->position[0] - 1]
            [(int)player_position->position[2]]) {

            // players x location decreases by 1
            player_position->position[0] -= 1;

            camera.position[0] =
                player_position->position[0] - 3.0f;

            player_moves = false;
        }

        if ((((mouseX < WINDOW_WIDTH / 2 + 20) &&
            (mouseY < WINDOW_HEIGHT / 2 - 5) &&
            player_moves) ||
            currentKeyStates[SDL_SCANCODE_A]) &&
            dungeon_level_current->map_cells
            [(int)player_position->position[0]]
            [(int)player_position->position[2] - 1]) {

            // player y location decreases by 1
            player_position->position[2] -= 1;

            camera.position[2] =
                player_position->position[2] + 3.0f;

            player_moves = false;
        }

        // update camera & view_matrix
        camera = Calc_Camera_View_Matrix(camera);

    // TODO: rendering functionality

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
        (float *) projection_matrix
    );

    glUniformMatrix4fv(
        view_matrix_loc,
        1,
        GL_FALSE,
        (float *) camera.view_matrix
    );

    glUniform3f(
        light_position_loc,
        light_position[0],
        light_position[1],
        light_position[2]
    );


    glUniform3f(
        light_color_loc,
        light_color[0],
        light_color[1],
        light_color[2]
    );

    float shine_damper = 8.0f;

    glUniform1f(
        shine_damper_loc,
        shine_damper
    );                          // roughness of surface low = rough

    float reflectivity = 1.0f; // % cloth = low// metal = med to high // water glass high //

    glUniform1f(
        reflectivity_loc,
        reflectivity
    );

    vec3 sky_color;

    sky_color[0] = 0.05f;
    sky_color[1] = 0.02f;
    sky_color[2] = 0.01f;

    glUniform3f(
        sky_color_loc,
        sky_color[0],
        sky_color[1],
        sky_color[2]
    );

    glUniform3f(
       camera_position_loc,
       camera.position[0],
       camera.position[1],
       camera.position[2]
    );

    //////////////////////// Render Dungeon Map //////////////////////////

    for (u8 x = 0; x <= MAP_WIDTH; x++) {

            for (u8 z = 0; z <= MAP_HEIGHT; z++) {

                if (dungeon_level_current->map_cells[x][z]) {

                    vec3 floor_position = {(float) x, 0.0f, (float) z};
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
                        (float *) floor.model_matrix
                    );

                    glDrawElements(                               // draw using Triangles
                        GL_TRIANGLES,
                        sizeof(index_array),
                        GL_UNSIGNED_INT,
                        (void *) 0
                    );
                }
            }
        } // end of map render

        glBindVertexArray(                          // set which VAO to draw
            player_model->vaoID
        );

        glUniformMatrix4fv(
            projection_matrix_loc,
            1,
            GL_FALSE,
            (float *) projection_matrix
        );

        glUniformMatrix4fv(
            view_matrix_loc,
            1,
            GL_FALSE,
            (float *) camera.view_matrix
        );

        vec3 scale = {1.0f, 1.0f, 1.0f};

        *player_model = Calc_Model_matrix(
            *player_model,
            player_position->position,
            0.0f,
            -45.0f,
            0.0f,
            scale
        );

        glUniformMatrix4fv(
            model_matrix_loc,
            1,
            GL_FALSE,
            (float *) player_model->model_matrix
        );

        glDrawElements(                               // draw using Triangles
            GL_TRIANGLES,
            player_model->num_indices,
            GL_UNSIGNED_INT,
            (void *) 0
        );

    ///////////////////////////////////////////////////////////

        glBindVertexArray(                          // disable the used VAO
            0
        );

    //////////////////////////////////////////////////////////

        // swap buffers for OpenGL

        SDL_GL_SwapWindow(
            window
        );

        SDL_Delay(                                 // give the cpu a well earned break !
            100
        );

    }   // end of the main game loop

//////////////////// Clean up and Exit //////////////////////////////

    // free up resources


    // cleanup OpenGL - anything stored on the gfx card.

    glDeleteProgram(
        shader
    );

    free(
        dungeon_level_current
    );

    Object_Cleanup();

    SDL_DestroyWindow(
        window
    );

    SDL_Quit();

    return 0;
}
