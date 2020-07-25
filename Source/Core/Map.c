//
// Created by frazor on 25/07/2020.
//

#include "Map.h"

Dungeon_Level_Current *Map_Create_Dungeon_Level(Dungeon_Level_Current *dungeon_level_current) {


    bool rooms_generating = true;
    u32 floor_tiles_used = 0;
    u32 room_count = 0;
    u8 old_room_width = 0;
    u8 old_room_height = 0;

    Point_3D room_location = {0.0f, 0.0f, 0.0f};
    Point_3D old_room_location = {0.0f, 0.0f, 0.0f};

    while (rooms_generating) {
        // make a random room with a max size and width
        u8 room_width = Dice_Roll(
            1,
            MAX_ROOM_WIDTH
        ) + 3;

        u8 room_height = Dice_Roll(
            1,
            MAX_ROOM_HEIGHT
        ) + 3;

        // place the room
        room_location.x = Dice_Roll(
            1,
            MAP_WIDTH - room_width
        );

        room_location.z = Dice_Roll(
            1,
            MAP_HEIGHT - room_height
        );

        // attempt tp place room into map.
        bool success = Map_Carve_Room(
            dungeon_level_current,
            room_location.x,
            room_location.z,
            room_width,
            room_height
        );

        if (success) {
            floor_tiles_used += (room_width) * (room_height);

//            if (room_count > 0) {
//                Map_Create_Corridor(
//                    dungeon_level_current,
//                    room_location,
//                    room_width,
//                    room_height,
//                    old_room_location,
//                    old_room_width,
//                    old_room_height
//                );
//            }
//
//
//            old_room_location.x = room_location.x;
//            old_room_location.z = room_location.z;
//            old_room_width = room_width;
//            old_room_height = room_height;
            room_count += 1;
        }

        // Exit condition
        if (((float) floor_tiles_used / (float) (MAP_WIDTH * MAP_HEIGHT)) > 0.45f) {
            rooms_generating = false;
        }
    }

    //printf("\nDungeon Level has generated %u Rooms\n", room_count);

    return dungeon_level_current;
}

void Map_Create_Corridor(
    Dungeon_Level_Current *dungeon_level_current,
    Point_3D room_location,
    u8 room_width,
    u8 room_height,
    Point_3D old_room_location,
    u8 old_room_width,
    u8 old_room_height) {

    // Generate corridors
    // every room has to be accessible by corridors.


    // step through each room and join it to the next room
    // by carving a corridor.

    // set 2 random initial points in each room.
    Point_3D from_point = Map_Random_Point_In_Room(old_room_location, old_room_width, old_room_height);
    Point_3D to_end_point = Map_Random_Point_In_Room(room_location, room_width, room_height);

    // walk along proposed corridor and create a segment list
    // TODO: (Frazor) from room to room, discard duplicate segments.
    Point_3D midpoint = {0.0f, 0.0f, 0.0f};

    if (Dice_Roll(1, 2) == 1) {
        // midpoint for carving horizontal then vertical
        midpoint.x = to_end_point.x;
        midpoint.z = from_point.z;
        Map_Carve_Corridor_Horizontal(dungeon_level_current, from_point, midpoint);
        Map_Carve_Corridor_Vertical(dungeon_level_current, midpoint, to_end_point);
    } else {
        // midpoint for carving vertical then horizontal
        midpoint.x = from_point.x;
        midpoint.z = to_end_point.z;
        Map_Carve_Corridor_Vertical(dungeon_level_current, from_point, midpoint);
        Map_Carve_Corridor_Horizontal(dungeon_level_current, midpoint, to_end_point);
    }
}

Point_3D Map_Random_Point_In_Room(
    Point_3D room_location,
    u8 room_width,
    u8 room_height) {

    Point_3D location = {0.0f, 0.0f, 0.0f};

    location.x = (float) Dice_Roll(
        1,
        room_width - 1
    ) + room_location.x - 1;

    location.z = (float) Dice_Roll(
        1,
        room_height - 1
    ) + room_location.z - 1;

    return location;
}

bool Map_Carve_Room(Dungeon_Level_Current *dungeon_level_current,
                    u32 x, u32 y, u32 width, u32 height) {

    // make sure that no two rooms over lap.
    for (uint i = x - 1; i < x + width + 1; i++) {
        for (uint j = y - 1; j < y + height + 1; j++) {
            if (dungeon_level_current->map_cells[i][j]) {
                return false;
            }
        }
    }

    // all clear - go ahead and make the room
    for (uint i = x; i < x + width; i++) {
        for (uint j = y; j < y + height; j++) {
            dungeon_level_current->map_cells[i][j] = true;
        }
    }

    return true;
}

void Map_Carve_Corridor_Horizontal(Dungeon_Level_Current *dungeon_level_current,
                                   Point_3D from, Point_3D to) {

    u8 first;
    u8 last;

    // which direction do we carve.
    if (from.x < to.x)                   // carve to the left
    {
        first = from.x;
        last = to.x;
    } else                                // carve right
    {
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

void Map_Carve_Corridor_Vertical(Dungeon_Level_Current *dungeon_level_current,
                                 Point_3D from, Point_3D to) {

    u8 first;
    u8 last;

    // which direction do we carve.
    if (from.z < to.z)                   // carve down
    {
        first = from.z;
        last = to.z;
    } else                                // carve up
    {
        first = to.z;
        last = from.z;
    }

    // carve first to last position.
    u8 x = from.x;
    for (u8 z = first; z <= last; z++) {
        dungeon_level_current->map_cells[x][z] = true;
    }
}
