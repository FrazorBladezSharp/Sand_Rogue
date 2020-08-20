//
// Created by frazor on 19/08/2020.
//

#include "Monster_AI.h"


static i32 monster_ai_map[MAP_WIDTH][MAP_HEIGHT];

void Monster_AI_Dijkstra_Map(
    i32 target_x,
    i32 target_z){
    // TODO : Correct this Logic !
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
