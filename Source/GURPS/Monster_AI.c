//
// Created by frazor on 19/08/2020.
//

#include "Monster_AI.h"

//typedef enum{
//
//    ACTION_NONE,              // check if needs to change
//    ACTION_MOVE,              // chase or stop chase
//    ACTION_ATTACK,            // find target else move (los) = use monster_ai_map 1 = attack 0
//    ACTION_RANGED_ATTACK,     // find target else move (los) = special attack
//    ACTION_ASLEEP             // have we been awakened
//
//    //ACTION_COUNT
//
//} Action;
//
//typedef enum{                     use the AI to determine the Action
//
//    MONSTERS_AI_NORMAL = 0,
//    MONSTERS_AI_MEAN = 1,
//    MONSTERS_AI_FLYING = 2,
//    MONSTERS_AI_REGEN = 4,
//    MONSTERS_AI_GREEDY = 8,
//    MONSTERS_AI_INVISIBLE = 16
//
//} Monsters_AI;

static i32 monster_ai_map[MAP_WIDTH][MAP_HEIGHT];

void Monster_AI_Dijkstra_Map(
    i32 target_x,
    i32 target_z){

    // we take 2 numbers ludicrously high = 9999 Target of interest = 0
    printf("AI START : %u\n", SDL_GetTicks());
    i32 target = 0;
    i32 high = 9999;

    // initialize the map to 9999
    for(i32 x = 0; x < MAP_WIDTH; x++){

        for(i32 z= 0; z <MAP_HEIGHT; z++){

            monster_ai_map[x][z] = high;
        }
    }
    // set the target or targets
    monster_ai_map[target_x][target_z] = target;

    // scan the Monster AI map until no changes are made
    bool changes = true;
    i32 changes_made = 0;
    Dungeon_Level_Current* current_level = Dungeon_level();

    while(changes){
        // Change any value that is not ludicrous :
        changes = false;

        for(i32 x = 1; x < MAP_WIDTH - 1; x++){

            for(i32 z= 1; z <MAP_HEIGHT - 1; z++){

                i32 current_floor_tile = monster_ai_map[x][z];
                i32 north = monster_ai_map[x][z - 1];
                i32 south = monster_ai_map[x][z + 1];
                i32 west = monster_ai_map[x - 1][z];
                i32 east = monster_ai_map[x + 1][z];

                if(current_floor_tile != high){
                    //          Check each direction (N.S.W.E.)
                    // North z_axis - 1
                    if((current_level->map_cells[x][z - 1]) &&
                       ( north > current_floor_tile + 1)){

                        //          increase their value to current location value + 1 if :
                        //                  it makes that location value lower and
                        //                  that location can be moved to (Accessible)
                        monster_ai_map[x][z - 1] = current_floor_tile + 1;
                        changes = true;
                        changes_made++;
                    }
                    // South z_axis + 1
                    if((current_level->map_cells[x][z + 1]) &&
                       (south > current_floor_tile + 1)){

                        //          increase their value to current location value + 1 if :
                        //                  it makes that location value lower and
                        //                  that location can be moved to (Accessible)
                        monster_ai_map[x][z + 1] = current_floor_tile + 1;
                        changes = true;
                        changes_made++;
                    }
                    // West  x_axis - 1
                    if((current_level->map_cells[x - 1][z]) &&
                       (west > current_floor_tile + 1)){

                        //          increase their value to current location value + 1 if :
                        //                  it makes that location value lower and
                        //                  that location can be moved to (Accessible)
                        monster_ai_map[x - 1][z] = current_floor_tile + 1;
                        changes = true;
                        changes_made++;
                    }
                    // East  x_axis + 1
                    if((current_level->map_cells[x + 1][z]) &&
                       (east > current_floor_tile + 1)){

                       //          increase their value to current location value + 1 if :
                       //                  it makes that location value lower and
                       //                  that location can be moved to (Accessible)
                       monster_ai_map[x + 1][z] = current_floor_tile + 1;
                       changes = true;
                       changes_made++;
                    }
                }
            }
        }
    }
    printf("End of AI map calculations %u\n", SDL_GetTicks());
    printf("Changes Made = %d\n", changes_made);
}

void Monster_AI_Register(
    Position* monster_position){

    monster_ai_map[(i32)monster_position->position[0]][(i32)monster_position->position[2]] = 9999;
}

bool Monster_AI_Mean(
    Position* monster_position){

    // move towards player or attack
    i32 x_axis = (i32)monster_position->position[0];
    i32 z_axis = (i32)monster_position->position[2];
    i32 ai_map_value = monster_ai_map[x_axis][z_axis];

    // if ai map value is > 1 then we move
    if(ai_map_value > 1){

        bool north = false;
        bool south = false;
        bool west = false;
        bool east = false;

        // note we are not allowed to move to a 9999 tile.
        //check cardinal direction, set new position if available.
        // North -1 z_axis
        if(monster_ai_map[x_axis][z_axis - 1] == ai_map_value){

            if(Dice_Roll(1,6) >=3){
                north = true;
            }
        }
        if(monster_ai_map[x_axis][z_axis - 1] < ai_map_value){

            north = true;
        }
        // South +1 z_axis
        if(monster_ai_map[x_axis][z_axis + 1] == ai_map_value){

            if(Dice_Roll(1,6) >=3){
                south = true;
            }
        }
        if(monster_ai_map[x_axis][z_axis + 1] < ai_map_value){

            south = true;
        }
        // West -1 x_axis
        if(monster_ai_map[x_axis - 1][z_axis] == ai_map_value){

            if(Dice_Roll(1,6) >=3){
                west = true;
            }
        }
        if(monster_ai_map[x_axis - 1][z_axis] < ai_map_value){

            west = true;
        }
        // East +1 x_axis
        if(monster_ai_map[x_axis + 1][z_axis] == ai_map_value){

            if(Dice_Roll(1,6) >=3){
                east = true;
            }
        }
        if(monster_ai_map[x_axis + 1][z_axis] < ai_map_value){

            east = true;
        }
        // decide which true value to use
        // possible outcome =  1, 2, 3, 4 True's
        if(north){

            monster_position->position[2] = z_axis - 1;
        }
        if(south){

            if(monster_position->position[2] != z_axis){

                if(Dice_Roll(1,6) >=3){

                    monster_position->position[2] = z_axis + 1;
                }
            }else {
                monster_position->position[2] = z_axis + 1;
            }
        }

        if(west){

            monster_position->position[0] = x_axis - 1;
        }
        if(east){

            if(monster_position->position[0] != x_axis){

                if(Dice_Roll(1,6) >=3){

                    monster_position->position[0] = x_axis + 1;
                }
            }else {
                monster_position->position[0] = x_axis + 1;
            }
        }

        // optional test if both ns and we move has been made
        // and reset 1 of the moves to the original x_axis or z_axis.

        // return false for attack
        return false;
    }

    // if value < 2 then attack
    if(ai_map_value < 2){

        // return true for attack
        return true;
    }

    return false;
}
