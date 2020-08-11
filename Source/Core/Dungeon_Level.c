//
// Created by frazor on 08/08/2020.
//

#include "Dungeon_Level.h"


static Dungeon_Level_Current *dungeon_level_current;

void Dungeon_Level_Initialize(){

    dungeon_level_current = (Dungeon_Level_Current *) malloc(
        sizeof(Dungeon_Level_Current)
    );
}

void Dungeon_Level_New(i8 dungeon_level){

    dungeon_level_current->dungeon_level = dungeon_level;
    // set all locations to false.
    for (int x = 0; x <= MAP_WIDTH; x++) {

        for (int y = 0; y <= MAP_HEIGHT; y++) {

            dungeon_level_current->map_cells[x][y] = false;
        }
    }

    dungeon_level_current = Map_Create_Dungeon_Level(
        dungeon_level_current
    );
}

Position* Dungeon_Place_Player(
    Position* position){

    Point_3D place = Map_Random_Point_In_Room(0);

    position->position[0] = place.x;
    position->position[1] = 0.5f;
    position->position[2] = place.z;

    return position;
}

Dungeon_Level_Current* Dungeon_level(){
    return dungeon_level_current;
}

void Dungeon_Level_Cleanup(){

    free(
        dungeon_level_current
    );
}
