//
// Created by frazor on 30/07/2020.
//

#include "User_Input.h"

Current_Game_State User_Keyboard_Input(
    Current_Game_State* current_game_state,
    Position* players_current_position,
    Dungeon_Level_Current* dungeon_level_current,
    Position* monster_position)
{
    const u8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if(currentKeyStates[SDL_SCANCODE_PERIOD]){
        Injuries_Healing_Update(true, current_game_state);
    }
    // determine which of the 4 directions to move - 1 square
    // with community permission increase to 8 way.

    Position players_old_position = {

            players_current_position->object_id,
            players_current_position->position[0],
            players_current_position->position[1],
            players_current_position->position[2],
    };

    bool back = dungeon_level_current->map_cells
        [(int)players_current_position->position[0] - 1]
        [(int)players_current_position->position[2]];

    bool forward = dungeon_level_current->map_cells
        [(int)players_current_position->position[0] + 1]
        [(int)players_current_position->position[2]];

    bool left = dungeon_level_current->map_cells
        [(int)players_current_position->position[0]]
        [(int)players_current_position->position[2] - 1];

    bool right = dungeon_level_current->map_cells
        [(int)players_current_position->position[0]]
        [(int)players_current_position->position[2] + 1];

    if(currentKeyStates[SDL_SCANCODE_S] && back){

        // players x location decreases by 1
        players_current_position->position[0] -= 1;

        current_game_state->main_camera.position[0] =
            players_current_position->position[0] - 3.0f;
    }
    else if (currentKeyStates[SDL_SCANCODE_W] && forward) {

        // players x location increases by 1
        players_current_position->position[0] += 1;

        current_game_state->main_camera.position[0] =
            players_current_position->position[0] - 3.0f;
    }

    if (currentKeyStates[SDL_SCANCODE_D] && right) {

        // player y location increases by 1
        players_current_position->position[2] += 1;

        current_game_state->main_camera.position[2] =
            players_current_position->position[2] + 3.0f;
    }
    else if (currentKeyStates[SDL_SCANCODE_A] && left) {

        // player y location decreases by 1
        players_current_position->position[2] -= 1;

        current_game_state->main_camera.position[2] =
            players_current_position->position[2] + 3.0f;
    }

    // update camera & view_matrix
    current_game_state->main_camera = Calc_Camera_View_Matrix(
            current_game_state->main_camera
    );

    if((players_current_position->position[0] == monster_position->position[0])
        &&
        (players_current_position->position[2] == monster_position->position[2])){

        current_game_state->players_current_action = ACTION_ATTACK;

        // revert player back to their players_old_position
        players_current_position->position[0] = players_old_position.position[0];
        players_current_position->position[2] = players_old_position.position[2];
    }

    if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {

        current_game_state->game_is_running = false;
    }

    return *current_game_state;
}
