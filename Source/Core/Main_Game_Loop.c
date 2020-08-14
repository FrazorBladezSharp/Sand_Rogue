//
// Created by frazor on 30/07/2020.
//
/*
 * eg a * ( condition for a ) + b * ( condition for b ) + etc ...
 */
#include "Main_Game_Loop.h"

void Main_Game_Loop(
    Shader shader,
    SDL_Window* window)
{
    // our main game loop Starts Here
    Dice_Initialize();

    Game_Model floor_model = Sand_Floor_Tile_3D_Create(window);

    Dungeon_Level_Initialize();
    Dungeon_Level_New(1);
    Dungeon_Level_Current* dungeon_level_current = Dungeon_level();

    Position* player_position = (Position*)Object_Lookup_Component(
        64,
        COMP_POSITION
    );

    Secondary_Characteristics* player_secondary =
        (Secondary_Characteristics*)Object_Lookup_Component(
            64,
            COMP_SECONDARY_CHARACTERISTICS
    );

    // place player
    // TODO : place player
    player_position = Dungeon_Place_Player(
        player_position
    );


    // camera
    // TODO : (Valgrind) change camera to a static local_global pointer
    // currently the camera is causing uninitialised memory error.
    Main_Camera camera;

    camera.position[0] = player_position->position[0] - 3.0f;
    camera.position[1] = 6.6f;
    camera.position[2] = player_position->position[2] + 3.0f;
    camera.rotationX = 60.0f;
    camera.rotationY = 45.0f;
    glm_mat4_identity(camera.view_matrix);

    camera = Calc_Camera_View_Matrix(
        camera
    );

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
    Vector render_models;
    Vector_Init(&render_models);
    Vector_Append(&render_models, 64);       // adds player to be rendered

    Current_Game_State current_game_state = {

        .game_is_running = true,
        .main_camera = camera,
        .players_current_action = ACTION_NONE,
        .models_to_render = render_models
    };

    // add Object to render (&render_models)
    current_game_state =  Object_Add_Doors_To_Render(current_game_state);
    // add Test Monster
    current_game_state = Object_Add_Monster_To_Render(current_game_state);


    SDL_Event event;

    while (current_game_state.game_is_running) {

        current_game_state.players_current_action = ACTION_NONE;
        player_secondary->action_current = ACTION_NONE;


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
                player_position,
                dungeon_level_current
            );

            if(current_game_state.players_current_action ==
                ACTION_ATTACK){

                player_secondary->action_current = ACTION_ATTACK;
            }
        } // end of Game Update.

        //////////////////////////////////////////////////////////

        Render_all(
            shader,
            floor_model,
            projection_matrix,
            current_game_state,
            light_position,
            light_color,
            dungeon_level_current
        );

        // swap buffers for OpenGL

        SDL_GL_SwapWindow(
            window
        );

        SDL_Delay(                                 // give the cpu a well earned break !
            10                                 // high value due to keyboard input
        );

    }   // end of the main game loop

    Vector_Free_Memory(&render_models);
}
