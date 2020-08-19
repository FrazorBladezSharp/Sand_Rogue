//
// Created by frazor on 10/08/2020.
//

#include "Items_Fixtures.h"

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

    // Door 43      +
    Items_Load_Model(
        43,
        color,
        "Resource/Models/Ascii_3D/+.obj",
        vao_storage,
        vbo_storage,
        model_component,
        object
    );

    // Stairs Down  62  >
    Items_Load_Model(
        62,
        color,
        "Resource/Models/Ascii_3D/Greater_Than.obj",
        vao_storage,
        vbo_storage,
        model_component,
        object
    );

    // Armor    93      ]
    Items_Load_Model(
        93,
        color,
        "Resource/Models/Ascii_3D/Armor.obj",
        vao_storage,
        vbo_storage,
        model_component,
        object
    );
    // Weapon   41      )
    Items_Load_Model(
        41,
        color,
        "Resource/Models/Ascii_3D/Weapon.obj",
        vao_storage,
        vbo_storage,
        model_component,
        object
    );
    // Rings    61      =
    Items_Load_Model(
        61,
        color,
        "Resource/Models/Ascii_3D/Rings.obj",
        vao_storage,
        vbo_storage,
        model_component,
        object
    );
    // Potions  33      !
    Items_Load_Model(
        33,
        color,
        "Resource/Models/Ascii_3D/Potions.obj",
        vao_storage,
        vbo_storage,
        model_component,
        object
    );
    // Rods     47      /
    Items_Load_Model(
        47,
        color,
        "Resource/Models/Ascii_3D/Rods.obj",
        vao_storage,
        vbo_storage,
        model_component,
        object
    );
    // Scrolls  63      ?
    Items_Load_Model(
        63,
        color,
        "Resource/Models/Ascii_3D/Scrolls.obj",
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

    object->object_id = object_id;

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

Dungeon_Level_Current* Items_Add_Fixtures_To_Level()
{
    Dungeon_Place_Doors();
    Dungeon_Place_Stairs();

    Dungeon_Level_Current* ret = Dungeon_level();

    return ret;
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
