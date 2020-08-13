//
// Created by frazor on 10/08/2020.
//

#include "Items_Fixtures.h"

// TODO: Initialize Models
void Items_Initialize_Models(
    Vector *vao_storage,
    Vector *vbo_storage,
    Game_Model *model_component,
    Game_Object *object
){
//    char buffer[126];

//        sprintf(
//            buffer,
//            "Resource/Models/Ascii_3D/%c.obj",
//            index
//        );
    vec4 color = {0.5f, 0.25f, 0.1f, 1.0f};

    Items_Load_Model(
        43,
        color,
        "Resource/Models/Ascii_3D/+.obj",
        vao_storage,
        vbo_storage,
        model_component,
        object
    );

}

void Items_Load_Model(
    i32 object_id,
    vec4 color,
    const char* file_path,
    Vector *vao_storage,
    Vector *vbo_storage,
    Game_Model *model_component,
    Game_Object *object){

    Game_Model *object_model;

    object_model = Load_Model_3D(   // memory is allocated by the model loader.
        file_path,
        color,
        vao_storage,
        vbo_storage
    );

    object_model->object_id = object_id;

    model_component[object->object_id].object_id = object_id;
    object[object_id].component[COMP_MODEL] = object_model;
}

//void Items_Initialize_Models()
//{
// armour  as above location  93          ]       object cycle through objects to place them
// weapon as above location   41          )       object
// rings  as above             61          =       object
// potions : as above location 33          !       object
// rods & staves  as above     47          /       object
// scrolls  as above           63          ?       object
// food  as above              58          :       object

// gold  as above              42          *  #define GOLD_CALC (rnd(50 + 10 * level) + 2)
// chance per room ((rnd(3) == 3) && (! has not seen amulet || (level >= max_level))) thing = gold
// stairs down  as above       62          >       thing
// stairs up  as above         60          <       thing
// Trap  as above              94          ^       thing
// Doors  as above            43          +       thing
//}

void Items_Add_Fixtures_To_Level()
{
    Dungeon_Place_Doors();
    Dungeon_Place_Stairs();
    // TODO: Add Fixtures to Level
// stairs down  as above       62          >       thing
// stairs up  as above         60          <       thing
// Trap  as above              94          ^       thing
// Doors  as above            43          +       thing

}

void Items_Add_to_Room(i32 number_of_dungeon_rooms)
{
    // TODO: add room Contents when door is opened
// Room_Contents. room_contents[index] room = dark (rnd(10) < (level - 1))
// MAX CONTENTS PER LEVEL max things = num rooms  max objects = num_rooms
// things = stairs doors gold & objects
// objects = items 35% per max_object then pick random object
// items & location

// chance per room (rnd(100) < (gold value > 0 ? 80 : 25))

// armour as above location  93          ]       object cycle through objects to place them
// weapon  as above location   41          )       object
// rings  as above             61          =       object
// potions  as above location 33          !       object
// rods & staves  as above     47          /       object
// scrolls  as above           63          ?       object
// food  as above              58          :       object

// gold  as above              42          *  #define GOLD_CALC (rnd(50 + 10 * level) + 2)
// chance per room ((rnd(3) == 3) && (! has not seen amulet || (level >= max_level))) thing = gold


}
