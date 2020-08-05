//
// Created by frazor on 30/07/2020.
//
/* TODO: think about if statements as they can be taken out
 * eg a * ( condition for a ) + b * ( condition for b ) + etc ...
 */
#include "Main_Game_Loop.h"

void Main_Game_Loop(
    Shader shader,
    Dungeon_Level_Current* dungeon_level_current,
    Game_Model floor_model,
    SDL_Window* window)
{
    // our main game loop Starts Here

    Position* player_position = (Position*)Object_Lookup_Component(
        64,
        COMP_POSITION
    );

    Position* monster_position = (Position*)Object_Lookup_Component(
        77,
        COMP_POSITION
    );

    Game_Model* player_model = (Game_Model*)Object_Lookup_Component(
        64,
        COMP_MODEL
    );

    Game_Model* monster_model = (Game_Model*)Object_Lookup_Component(
        77,
        COMP_MODEL
    );

    Primary_Characteristics* player_primary =
        (Primary_Characteristics*)Object_Lookup_Component(
            64,
            COMP_PRIMARY_CHARACTERISTICS
    );

    Primary_Characteristics* monster_primary =
        (Primary_Characteristics*)Object_Lookup_Component(
            77,
            COMP_PRIMARY_CHARACTERISTICS
    );

    Secondary_Characteristics* player_secondary =
        (Secondary_Characteristics*)Object_Lookup_Component(
            64,
            COMP_SECONDARY_CHARACTERISTICS
    );

    Secondary_Characteristics* monster_secondary =
        (Secondary_Characteristics*)Object_Lookup_Component(
            77,
            COMP_SECONDARY_CHARACTERISTICS
    );

    glUseProgram(
        shader.shader_program
    );

    /////////////////// Matrix locations in Shader ////////////////



    /////////////////////////////////////////////////////////////

    // camera
    Main_Camera camera;
    mat4 projection_matrix;

    camera.position[0] = player_position->position[0] - 3.0f;
    camera.position[1] = 6.6f;
    camera.position[2] = player_position->position[2] + 3.0f;
    camera.rotationX = 60.0f;
    camera.rotationY = 45.0f;

    camera = Calc_Camera_View_Matrix(
        camera
    );

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
    Current_Game_State current_game_state = {

        .game_is_running = true,
        .main_camera = camera,
        .players_current_position = player_position,
        .players_current_action = ACTION_NONE
    };

    SDL_Event event;
    //i32 mouseX;
    //i32 mouseY;

    while (current_game_state.game_is_running) {

        //mouseX = 0;
        //mouseY = 0;
        current_game_state.players_current_action = ACTION_NONE;
        player_secondary->action_current = ACTION_NONE;
        monster_secondary->action_current = ACTION_NONE;

        while (SDL_PollEvent(&event) == SDL_TRUE) {
        /*
         * a * ( condition for a ) +
         * current_game_state.game_is_running = false *(event.type == SDL_QUIT);
         *
         */


            if (event.type == SDL_QUIT) {

                current_game_state.game_is_running = false;
            }

            if(event.type == SDL_KEYDOWN){

                player_secondary->action_current = ACTION_MOVE;
                current_game_state.players_current_action = ACTION_MOVE;
            }

        } // end of Poll event loop

        ///////////////// Game Update //////////////////////////

        if(current_game_state.players_current_action != ACTION_NONE){

            // we update the whole system
            current_game_state =  User_Keyboard_Input(
                current_game_state,
                dungeon_level_current,
                monster_position
            );

            i32 attack_result = 0;
            i32 monster_attack_result = 0;

            if(current_game_state.players_current_action ==
                ACTION_ATTACK){

                player_secondary->action_current = ACTION_ATTACK;
                monster_secondary->action_current = ACTION_ATTACK;

                attack_result = Sand_Attack_Roll(
                    64,
                    77
                );

                monster_attack_result = Sand_Attack_Roll(
                    77,
                    64
                );

                printf(
                    "(%d)You punch for %d Damage : Health Status = %d\n",
                    player_secondary->hit_points_current,
                    attack_result,
                    player_primary->health_status
                );

                printf(
                    "(%d)The Monster does %d damage : Health Status = %d\n",
                    monster_secondary->hit_points_current,
                    monster_attack_result,
                    monster_primary->health_status
                );
            }

            Damage_Melee(
                monster_secondary->action_current,
                64,
                monster_attack_result
            );

            Damage_Melee(
                player_secondary->action_current,
                77,
                attack_result
            );
        } // end of Game Update.

        ///////////////// Render ////////////////////////////////

        // TODO: rendering functionality

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        glUseProgram(
            shader.shader_program
        );

        glBindVertexArray(                          // set which VAO to draw
            floor_model.vaoID
        );
        /* this could be made into an enum and moved to common.h
     * model_matrix_loc = 0
     * view_matrix_loc = 1
     * projection_matrix_loc = 2
     * light_position_loc = 3
     * light_color_loc = 4
     * shine_damper_loc = 5
     * reflectivity_loc = 6
     * sky_color_loc = 7
     * camera_position_loc = 8
     */
        glUniformMatrix4fv(
            shader.uniform_Locations[2],
            1,
            GL_FALSE,
            (float *) projection_matrix
        );

        glUniformMatrix4fv(
            shader.uniform_Locations[1],
            1,
            GL_FALSE,
            (float *) current_game_state.main_camera.view_matrix
        );

        glUniform3f(
            shader.uniform_Locations[3],
            light_position[0],
            light_position[1],
            light_position[2]
        );

        glUniform3f(
            shader.uniform_Locations[4],
            light_color[0],
            light_color[1],
            light_color[2]
        );

        float shine_damper = 8.0f;

        glUniform1f(
            shader.uniform_Locations[5],
            shine_damper
        );                          // roughness of surface low = rough

        float reflectivity = 1.0f; // % cloth = low// metal = med to high // water glass high //

        glUniform1f(
            shader.uniform_Locations[6],
            reflectivity
        );

        vec3 sky_color;

        sky_color[0] = 0.05f;
        sky_color[1] = 0.02f;
        sky_color[2] = 0.01f;

        glUniform3f(
            shader.uniform_Locations[7],
            sky_color[0],
            sky_color[1],
            sky_color[2]
        );

        glUniform3f(
            shader.uniform_Locations[8],
            current_game_state.main_camera.position[0],
            current_game_state.main_camera.position[1],
            current_game_state.main_camera.position[2]
        );

        //////////////////////// Render Dungeon Map //////////////////////////

        for (u8 x = 0; x <= MAP_WIDTH; x++) {

            for (u8 z = 0; z <= MAP_HEIGHT; z++) {

                if (dungeon_level_current->map_cells[x][z]) {

                    vec3 floor_position = {(float) x, 0.0f, (float) z};

                    Position current_floor_position = {
                        0,
                        floor_position[0],
                        floor_position[1],
                        floor_position[2],
                        0.0f,
                        0.0f,
                        0.0f,
                        1.0f
                    };

                    floor_model = Calc_Model_matrix(
                        floor_model,
                        &current_floor_position
                    );

                    glUniformMatrix4fv(
                        shader.uniform_Locations[0],
                        1,
                        GL_FALSE,
                        (float *) floor_model.model_matrix
                    );

                    glDrawElements(                               // draw using Triangles
                        GL_TRIANGLES,
                        floor_model.num_indices,
                        GL_UNSIGNED_INT,
                        (void *) 0
                    );
                }
            }
        } // end of map render

        ////////////////////////////////// render Player ////////////////////////////////////////

        glBindVertexArray(                          // set which VAO to draw
            player_model->vaoID
        );

        glUniformMatrix4fv(
            shader.uniform_Locations[2],
            1,
            GL_FALSE,
            (float *) projection_matrix
        );

        glUniformMatrix4fv(
            shader.uniform_Locations[1],
            1,
            GL_FALSE,
            (float *) current_game_state.main_camera.view_matrix
        );

        *player_model = Calc_Model_matrix(
            *player_model,
            current_game_state.players_current_position
        );

        glUniformMatrix4fv(
            shader.uniform_Locations[0],
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

        glBindVertexArray(                          // set which VAO to draw
            monster_model->vaoID
        );

        glUniformMatrix4fv(
            shader.uniform_Locations[2],
            1,
            GL_FALSE,
            (float *) projection_matrix
        );

        glUniformMatrix4fv(
            shader.uniform_Locations[1],
            1,
            GL_FALSE,
            (float *) current_game_state.main_camera.view_matrix
        );

        *monster_model = Calc_Model_matrix(
            *monster_model,
            monster_position
        );

        glUniformMatrix4fv(
            shader.uniform_Locations[0],
            1,
            GL_FALSE,
            (float *) monster_model->model_matrix
        );

        glDrawElements(                               // draw using Triangles
            GL_TRIANGLES,
            monster_model->num_indices,
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
            10                                 // high value due to keyboard input
        );

    }   // end of the main game loop
}
