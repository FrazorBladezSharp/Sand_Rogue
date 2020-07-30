//
// Created by frazor on 30/07/2020.
//

#include "User_Input.h"

Current_Game_State User_Input(
    Current_Game_State current_game_state,
    i32 mouseX,
    i32 mouseY,
    Dungeon_Level_Current* dungeon_level_current)
{
    // (Frazor) camera movement for debug
    const u8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
        current_game_state.game_is_running = false;
    }

    if (currentKeyStates[SDL_SCANCODE_W] &&
        currentKeyStates[SDL_SCANCODE_LSHIFT]) {

        current_game_state.main_camera.position[2] =
            current_game_state.main_camera.position[2] - 0.1f;

    } else if (currentKeyStates[SDL_SCANCODE_S] &&
               currentKeyStates[SDL_SCANCODE_LSHIFT]) {

        current_game_state.main_camera.position[2] =
            current_game_state.main_camera.position[2] + 0.1f;
    }

    if (currentKeyStates[SDL_SCANCODE_A] &&
        currentKeyStates[SDL_SCANCODE_LSHIFT]) {

        current_game_state.main_camera.position[0] =
            current_game_state.main_camera.position[0] - 0.1f;

    } else if (currentKeyStates[SDL_SCANCODE_D] &&
               currentKeyStates[SDL_SCANCODE_LSHIFT]) {

        current_game_state.main_camera.position[0] =
            current_game_state.main_camera.position[0] + 0.1f;
    }

    if (currentKeyStates[SDL_SCANCODE_Q] &&
        currentKeyStates[SDL_SCANCODE_LSHIFT]) {

        current_game_state.main_camera.position[1] =
            current_game_state.main_camera.position[1] - 0.1f;

    } else if (currentKeyStates[SDL_SCANCODE_E] &&
               currentKeyStates[SDL_SCANCODE_LSHIFT]) {

        current_game_state.main_camera.position[1] =
            current_game_state.main_camera.position[1] + 0.1f;
    }

    // Mouse R-click to move
    // get xy location of mouse
    // determine which of the 4 directions to move - 1 square
    // with community permission increase to 8 way.


    if ((((mouseX < WINDOW_WIDTH / 2 + 20) &&
                (mouseY > WINDOW_HEIGHT / 2 + 5))
                ||
                currentKeyStates[SDL_SCANCODE_S]) &&
                dungeon_level_current->map_cells
                [(int)current_game_state.players_current_position->position[0] - 1]
                [(int)current_game_state.players_current_position->position[2]]) {

        // players x location decreases by 1
        current_game_state.players_current_position->position[0] -= 1;

        current_game_state.main_camera.position[0] =
            current_game_state.players_current_position->position[0] - 3.0f;
    }
    else if ((((mouseX > WINDOW_WIDTH / 2 + 20) &&
               (mouseY < WINDOW_HEIGHT / 2 - 5))
              ||
              currentKeyStates[SDL_SCANCODE_W]) &&
             dungeon_level_current->map_cells
             [(int)current_game_state.players_current_position->position[0] + 1]
             [(int)current_game_state.players_current_position->position[2]]) {

        // players x location increases by 1
        current_game_state.players_current_position->position[0] += 1;

        current_game_state.main_camera.position[0] =
            current_game_state.players_current_position->position[0] - 3.0f;
    }

    if ((((mouseX > WINDOW_WIDTH / 2 + 20) &&
          (mouseY > WINDOW_HEIGHT / 2 + 5))
          ||
          currentKeyStates[SDL_SCANCODE_D]) &&
          dungeon_level_current->map_cells
          [(int)current_game_state.players_current_position->position[0]]
          [(int)current_game_state.players_current_position->position[2] + 1]) {

        // player y location increases by 1
        current_game_state.players_current_position->position[2] += 1;

        current_game_state.main_camera.position[2] =
            current_game_state.players_current_position->position[2] + 3.0f;
    }
    else if ((((mouseX < WINDOW_WIDTH / 2 + 20) &&
                 (mouseY < WINDOW_HEIGHT / 2 - 5))
                 &&
                 currentKeyStates[SDL_SCANCODE_A]) &&
                 dungeon_level_current->map_cells
                 [(int)current_game_state.players_current_position->position[0]]
                 [(int)current_game_state.players_current_position->position[2] - 1]) {

    // TODO : logic for this section is wrong as A and S have the same truth output for TRUE
    // TODO : I believe this to be the same case for W and D.

        // player y location decreases by 1
        current_game_state.players_current_position->position[2] -= 1;

        current_game_state.main_camera.position[2] =
            current_game_state.players_current_position->position[2] + 3.0f;
    }

    // update camera & view_matrix
    current_game_state.main_camera = Calc_Camera_View_Matrix(
            current_game_state.main_camera
    );

    return current_game_state;
}
