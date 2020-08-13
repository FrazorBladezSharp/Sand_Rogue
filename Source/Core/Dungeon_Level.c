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
            dungeon_level_current->map_fixtures[x][y] = 0;
        }
    }

    dungeon_level_current = Map_Create_Dungeon_Level(
        dungeon_level_current
    );
}

void Dungeon_Level_Add_Items_Fixtures(i32 item_fixture_id, i32 x, i32 z)
{
    dungeon_level_current->map_fixtures[x][z] = item_fixture_id;
    printf("adding %d to location x : %d, z : %d\n", item_fixture_id, x, z);
}

void Dungeon_Place_Doors()
{
    i32 number_of_rooms = 0; //Map_Number_Of_Rooms();

    for(i32 index = 0; index <= number_of_rooms; index++){

        Dungeon_Level_Rooms* current_room = Map_Lookup_Room(index);
        // this gives locationX & LocationY as top left map point

        i32 x_axis = current_room->locationX;
        i32 z_axis = current_room->locationZ;

        i32 width = current_room->width;
        i32 breadth = current_room->breadth;


        // also gives Breadth(X) & Height(Z)(negative to positive)
        /*
         *      *******
         *      *     *
         *      *******
         */
        // check along west wall for corridors
        // start at Z and go positive Height.
        for(i32 z = z_axis; z <= width; z++){

            if(dungeon_level_current->map_cells[x_axis][z]){

                Dungeon_Level_Add_Items_Fixtures(43, x_axis, z);
            }
        }

        // check along north wall for corridors
        // start at X and go positive Breadth

        // check along east wall for corridors +1 in x-axis
        // start at Z + Breadth and go to positive Height
//        for(i32 z = z_axis + breadth; z <= width; z++){
//
//            if(dungeon_level_current->map_cells[x_axis - 1][z]){
//
//                Dungeon_Level_Add_Items_Fixtures(43, x_axis, z);
//            }
//        }

        // check along south wall for corridors +1 in z-axis
        // start at X + Height and go positive Breadth
    }
}

void Dungeon_Place_Stairs()
{
    Point_3D place = Map_Random_Point_In_Room(1);
    Dungeon_Level_Add_Items_Fixtures(62, place.x, place.z);
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
