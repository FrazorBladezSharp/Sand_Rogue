//
// Created by frazor on 19/08/2020.
//

#include "Monster_AI.h"


static i32 ai_map[MAP_WIDTH][MAP_HEIGHT];

void Monster_AI_Djikstra_Map(
    i32 target_x,
    i32 target_z){

    // we take 2 numbers ludicrously high = 9999 Target of interest = 0
    printf("AI START : %u\n", SDL_GetTicks());
    i32 target = 0;
    i32 high = 9999;

    // initialize the map to 9999
    for(i32 x = 0; x < MAP_WIDTH; x++){

        for(i32 z= 0; z <MAP_HEIGHT; z++){

            ai_map[x][z] = high;
        }
    }
    // set the target or targets
    ai_map[target_x][target_z] = target;

    // scan the Dungeon Level map until no changes are made
    bool changes = true;
    Dungeon_Level_Current* current_level = Dungeon_level();

    while(changes){
        // Change any value that is not ludicrous :
        changes = false;

        for(i32 x = 1; x < MAP_WIDTH - 1; x++){

            for(i32 z= 1; z <MAP_HEIGHT - 1; z++){

                i32 current_floor_tile = ai_map[x][z];
                i32 north = ai_map[x][z - 1];
                i32 south = ai_map[x][z + 1];
                i32 west = ai_map[x - 1][z];
                i32 east = ai_map[x + 1][z];

                if(current_floor_tile != high){
                    //          Check each direction (N.S.W.E.)
                    // North z_axis - 1

                    if((north < high) &&
                       (current_level->map_cells[x][z - 1])){

                        //          increase their value to current location value + 1 if :
                        //                  it makes that location value lower and
                        //                  that location can be moved to (Accessible)
                        if(north > current_floor_tile + 1){

                            north = current_floor_tile + 1;
                            changes = true;
                        }
                    }
                    // South z_axis + 1
                    if((south < high) &&
                       (current_level->map_cells[x][z + 1])){

                        //          increase their value to current location value + 1 if :
                        //                  it makes that location value lower and
                        //                  that location can be moved to (Accessible)
                        if(south > current_floor_tile + 1){

                            south = current_floor_tile + 1;
                            changes = true;
                        }
                    }
                    // West  x_axis - 1
                    if((west < high) &&
                       (current_level->map_cells[x - 1][z])){

                        //          increase their value to current location value + 1 if :
                        //                  it makes that location value lower and
                        //                  that location can be moved to (Accessible)
                        if(west > current_floor_tile + 1){

                            west = current_floor_tile + 1;
                            changes = true;
                        }
                    }
                    // East  x_axis + 1
                    if((east < high) &&
                       (current_level->map_cells[x + 1][z])){

                        //          increase their value to current location value + 1 if :
                        //                  it makes that location value lower and
                        //                  that location can be moved to (Accessible)
                        if(east > current_floor_tile + 1){

                            east = current_floor_tile + 1;
                            changes = true;
                        }
                    }
                }
            }
        }
    }
    printf("End of AI map calculations %u\n", SDL_GetTicks());
}
