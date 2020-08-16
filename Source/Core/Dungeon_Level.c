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
}

void Dungeon_Place_Doors()
{
    i32 door_id = 43;
    i32 number_of_rooms = Map_Number_Of_Rooms();

    for(i32 index = 0; index <= number_of_rooms; index++){

        Dungeon_Level_Rooms* current_room = Map_Lookup_Room(index);
        // this gives locationX & LocationZ as top left map point


        i32 x_axis = current_room->locationX;
        i32 z_axis = current_room->locationZ;

        i32 room_width_x = current_room->width;
        i32 room_breadth_z = current_room->breadth;

        // north wall
        for(i32 i = x_axis; i < x_axis + room_width_x; i++){

            if(z_axis - 1 < 0) break;

            if(dungeon_level_current->map_cells[i][z_axis - 1]) {

                Dungeon_Level_Add_Items_Fixtures(
                    door_id,
                    i,
                    z_axis - 1
                );
            }
        }
        // south wall
        for(i32 i = x_axis; i < x_axis + room_width_x; i++){

            if(z_axis + room_breadth_z > MAP_HEIGHT) break;

            if(dungeon_level_current->map_cells[i][z_axis + room_breadth_z]) {

                Dungeon_Level_Add_Items_Fixtures(
                    door_id,
                    i,
                    z_axis + room_breadth_z
                );
            }
        }
        // west wall
        for(i32 i = z_axis; i < z_axis + room_breadth_z; i++){

            if(x_axis - 1 < 0) break;

            if(dungeon_level_current->map_cells[x_axis - 1][i]) {

                Dungeon_Level_Add_Items_Fixtures(
                    door_id,
                    x_axis - 1,
                    i
                );
            }
        }
        // east wall
        for(i32 i = z_axis; i < z_axis + room_breadth_z; i++){

            if(x_axis + room_width_x > MAP_WIDTH) break;

            if(dungeon_level_current->map_cells[x_axis + room_width_x][i]) {

                Dungeon_Level_Add_Items_Fixtures(
                    door_id,
                    x_axis + room_width_x,
                    i
                );
            }
        }
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

Position* Dungeon_Place_Monster(
    u32 current_room,
    Position* position){

    Point_3D place = Map_Random_Point_In_Room(current_room);
    // TODO : only place the monster if location is not occupied by the player or another monster.
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
