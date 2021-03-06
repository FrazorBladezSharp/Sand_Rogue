//
// Created by frazor on 25/07/2020.
//

#include "Map.h"

static u32 room_count;

Dungeon_Level_Rooms level_rooms[32];

Dungeon_Level_Current *Map_Create_Dungeon_Level(
    Dungeon_Level_Current *dungeon_level_current){

    bool rooms_generating = true;
    u8 fails = 0;
    u32 floor_tiles_used = 0;
    room_count = 0;

    Point_3D room_location = {
        0.0f,
        0.0f,
        0.0f
    };

    while (rooms_generating) {
        // make a random room with a max size and width
        u8 room_width_x = Dice_Roll(
            1,
            MAX_ROOM_WIDTH
        ) + 3;

        u8 room_breadth_z = Dice_Roll(
            1,
            MAX_ROOM_HEIGHT
        ) + 3;

        // place the room
        room_location.x = Dice_Roll(
            1,
            MAP_WIDTH - room_width_x
        );

        room_location.z = Dice_Roll(
            1,
            MAP_HEIGHT - room_breadth_z
        );

        // attempt tp place room into map.
        bool success = Map_Carve_Room(
            dungeon_level_current,
            room_location.x,
            room_location.z,
            room_width_x,
            room_breadth_z
        );

        if (success) {

            floor_tiles_used += (room_width_x) * (room_breadth_z);
            level_rooms[room_count].dungeon_level = dungeon_level_current->dungeon_level;
            level_rooms[room_count].discovered = false;
            level_rooms[room_count].locationX = room_location.x;
            level_rooms[room_count].locationY = 0;
            level_rooms[room_count].locationZ = room_location.z;
            level_rooms[room_count].width = room_width_x;
            level_rooms[room_count].breadth = room_breadth_z;
            level_rooms[room_count].height = 1; // height of ceiling (ie Y-axis)
            level_rooms[room_count].light = 1;

            if (room_count > 0) {
                Map_Create_Corridor(
                    dungeon_level_current,
                    room_count
                );
            }

            room_count += 1;
            fails = 0;

        } else{

            fails +=1;
        }

      if(fails > 24){                               // Exit condition
            rooms_generating = false;
        }
    }

    return dungeon_level_current;
}

void Map_Create_Corridor(
    Dungeon_Level_Current *dungeon_level_current,
    u32 current_room){

    // set 2 random initial points in each room.
    Point_3D from_point = Map_Random_Point_In_Room(
        current_room - 1
    );

    Point_3D to_end_point = Map_Random_Point_In_Room(
        current_room
    );

    Point_3D midpoint = {
        0.0f,
        0.0f,
        0.0f
    };

    if (Dice_Roll(1, 2) == 1) {

        // midpoint for carving horizontal then vertical
        midpoint.x = to_end_point.x;
        midpoint.z = from_point.z;

        Map_Carve_Corridor_Horizontal(
            dungeon_level_current,
            from_point, midpoint
        );

        Map_Carve_Corridor_Vertical(
            dungeon_level_current,
            midpoint, to_end_point
        );

    } else {

        // midpoint for carving vertical then horizontal
        midpoint.x = from_point.x;
        midpoint.z = to_end_point.z;

        Map_Carve_Corridor_Vertical(
            dungeon_level_current,
            from_point, midpoint
        );

        Map_Carve_Corridor_Horizontal(
            dungeon_level_current,
            midpoint, to_end_point
        );
    }
}

Point_3D Map_Random_Point_In_Room(
    u32 current_room){

    Point_3D location = {
        0.0f,
        0.0f,
        0.0f
    };

    location.x = (float) Dice_Roll(
        1,
        level_rooms[current_room].width - 1
    ) + level_rooms[current_room].locationX - 1;

    location.z = (float) Dice_Roll(
        1,
        level_rooms[current_room].breadth - 1
    ) + level_rooms[current_room].locationZ - 1;

    return location;
}

bool Map_Carve_Room(
    Dungeon_Level_Current *dungeon_level_current,
    u32 x,
    u32 y,
    u32 x_axis,
    u32 z_axis){

    // make sure that no two rooms over lap.
    for (uint i = x - 1; i < x + x_axis + 1; i++) {
        for (uint j = y - 1; j < y + z_axis + 1; j++) {
            if (dungeon_level_current->map_cells[i][j]) {
                return false;
            }
        }
    }

    // all clear - go ahead and make the room
    for (uint i = x; i < x + x_axis; i++) {
        for (uint j = y; j < y + z_axis; j++) {
            dungeon_level_current->map_cells[i][j] = true;
        }
    }

    return true;
}

void Map_Carve_Corridor_Horizontal(
    Dungeon_Level_Current *dungeon_level_current,
    Point_3D from,
    Point_3D to){

    u8 first;
    u8 last;

    // which direction do we carve.
    if(from.x < to.x)                   // carve to the left
    {
        first = from.x;
        last = to.x;
    }else{                                // carve right
        first = to.x;
        last = from.x;
    }

    // carve first to last position.
    // NOTE: our tile is drawn from its central (offset of +- 0.5f) position.
    u8 z = from.z;

    for (u8 x = first; x <= last; x++) {
        dungeon_level_current->map_cells[x][z] = true;
    }
}

void Map_Carve_Corridor_Vertical(
    Dungeon_Level_Current *dungeon_level_current,
    Point_3D from,
    Point_3D to){

    u8 first;
    u8 last;

    // which direction do we carve.
    if(from.z < to.z)                   // carve down
    {
        first = from.z;
        last = to.z;
    }else{                                // carve up

        first = to.z;
        last = from.z;
    }

    // carve first to last position.
    u8 x = from.x;

    for (u8 z = first; z <= last; z++) {
        dungeon_level_current->map_cells[x][z] = true;
    }
}

i32 Map_Number_Of_Rooms()
{
    return room_count;
}

Dungeon_Level_Rooms* Map_Lookup_Room(i32 room_number)
{
    return &level_rooms[room_number];
}


