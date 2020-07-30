//
// Created by frazor on 30/07/2020.
//

#include "Main_Game_Loop.h"

void Main_Game_Loop(
    GLint shader,
    Position * player_position,
    Dungeon_Level_Current* dungeon_level_current,
    Game_Model floor,
    Game_Model *player_model,
    SDL_Window* window)
{
    // our main game loop Starts Here

    glUseProgram(shader);

    /////////////////// Matrix locations in Shader ////////////////

    // TODO : This should be part of the Shader code.

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
                        floor.num_indices,
                        GL_UNSIGNED_INT,
                        (void *) 0
                    );
                }
            }
        } // end of map render

        ////////////////////////////////// render Player ////////////////////////////////////////

        glBindVertexArray(                          // set which VAO to draw
            player_model->vaoID             // TODO: use ecs
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

        *player_model = Calc_Model_matrix( // TODO: fix this to use ecs
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

        //////////////////// Render Monster ///////////////////////



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
}