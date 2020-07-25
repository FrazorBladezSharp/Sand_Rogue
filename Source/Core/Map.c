//
// Created by frazor on 25/07/2020.
//

#include "Map.h"

Dungeon_Level_Current* Map_Create_Dungeon_Level(Dungeon_Level_Current *dungeon_level_current){


    bool rooms_generating = true;
    uint floor_tiles_used = 0;

    while(rooms_generating)
    {
        // make a random room with a max size and width
        uint room_width = Dice_Roll(
            1,
            MAX_ROOM_WIDTH
        ) + 3;

        uint room_height = Dice_Roll(
            1,
            MAX_ROOM_HEIGHT
        ) + 3;

        // place the room
        uint position_x = Dice_Roll(
            1,
            MAP_WIDTH - room_width
        );

        uint position_y = Dice_Roll(
            1,
            MAP_HEIGHT - room_height
        );

        // attempt tp place room into map.
        bool success =  Map_Carve_Room(
            dungeon_level_current,
            position_x,
            position_y,
            room_width,
            room_height
        );

        if(success)
        {
            floor_tiles_used += (room_width) * (room_height);
        }

        // Exit condition
        if(((float)floor_tiles_used / (float)(MAP_WIDTH * MAP_HEIGHT)) > 0.45f)
        {
            rooms_generating = false;
        }
    }

    return dungeon_level_current;
}

Game_Component Map_Random_Point_In_Room(Game_Component position, u32 room){

    // TODO: (Frazor) place the player on the map in a random room
}

bool Map_Carve_Room(Dungeon_Level_Current *dungeon_level_current,
                    u32 x, u32 y, u32 width, u32 height){

    // make sure that no two rooms over lap.
    for(uint i = x - 1; i < x + width +1; i++){
        for(uint j = y - 1; j < y + height + 1; j++)
        {
            if(dungeon_level_current->map_cells[i][j])
            {
                return false;
            }
        }
    }

    // all clear - go ahead and make the room
    for(uint i = x; i < x + width; i++)
    {
        for(uint j = y; j < y + height; j++)
        {
            dungeon_level_current->map_cells[i][j] = true;
        }
    }

    return true;
}

void Map_Carve_Corridor_Horizontal(vec2 from, vec2 to){

}

void Map_Carve_Corridor_Vertical(vec2 from, vec2 to){

}