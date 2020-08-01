//
// Created by frazor on 29/07/2020.
//

#include "Game_Objects.h"

static Vector vao_storage;
static Vector vbo_storage;

static Game_Object object[MAX_ENTITIES];
static Game_Entities game_entities[MAX_ENTITIES];
static Position position_component[MAX_ENTITIES];
static Game_Model model_component[MAX_ENTITIES];
static Primary_Characteristics primary_characteristic_component[MAX_ENTITIES];
static Secondary_Characteristics secondary_characteristic_component[MAX_ENTITIES];
static Combat_Stats combat_stats[MAX_ENTITIES];

void Object_Initialize()
{
    Vector_init(&vao_storage);
    Vector_init(&vbo_storage);


    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize Entities
        game_entities->entity_id[index] = UNUSED;            // set all entities to unused
        object[index].object_id = UNUSED;
    }

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize components
        position_component[index].object_id = UNUSED;
        model_component[index].object_id = UNUSED;
        primary_characteristic_component[index].object_id = UNUSED;
        secondary_characteristic_component[index].object_id= UNUSED;
        combat_stats[index].object_id = UNUSED;
    }

    vec4 color_green = { 0.1f, 0.5f, 0.1f, 1.0f };
    vec4 color_red =   { 0.5f, 0.1f, 0.1f, 1.0f };

    Object_Create(
        64,                             // ascii for @ character
        color_green,
        "Resource/Models/Player.obj"
    );

    Object_Create(
        77,                             // ascii for M character
        color_red,
        "Resource/Models/Monster.obj"
    );
    //////// Test code ////////
    // this shows that we can detect if an entity exits and if its object exists
    // we tried a direct detection on Components with no result found yet.
    // found the code to detect component :
    //          if(object[object_id].component[for loop index] != (void*)UNUSED)
    ///////////////////////////
    for(i32 index = 0; index < MAX_ENTITIES; index++){

        if(object[index].object_id != UNUSED){

            printf("Object does exist %d !\n", object[index].object_id);
        }
    }

    for(i32 object_index = 0; object_index < MAX_ENTITIES; object_index++){

        if(game_entities->entity_id[object_index] != UNUSED){

            printf("Entity %d exists !\n", object_index);
        }
    }
    ////////////////////////////

}

void Object_Create(
    i32 ascii_character,
    vec4 color,
    const char* file_path)
{
    game_entities->entity_id[ascii_character] = ascii_character;         // register object as an entity
    object[ascii_character].object_id = ascii_character;                 // assign the object an entity id



    // NOTE: you must free the memory before game exit      *** NOTE ****

    //////////////////////// Position Component //////////////////////////

    Position *object_position;

    object_position = (Position *) malloc(
        sizeof(Position)
    );

    object_position->object_id = ascii_character;          // set values for the object position.

    object_position->position[0] = 0.0f;                   // initialize all to zero
    object_position->position[1] = 0.5f;
    object_position->position[2] = 0.0f;
    object_position->rotationX = 0.0f;
    object_position->rotationY = -45.0f;
    object_position->rotationZ = 0.0f;
    object_position->scale = 1.0f;

    position_component[object->object_id].object_id = ascii_character;    // keep track of all position components
    object->component[COMP_POSITION] = object_position;                     // add position component to object

    ////////////////////////// Model Component ///////////////////////////

    Game_Model *object_model;

    //object_model = (Game_Model *) malloc(sizeof(Game_Model));
    object_model = Load_Model_3D(
        file_path,
        color,
        &vao_storage,
        &vbo_storage
    );

    object_model[ascii_character].object_id = ascii_character;
    model_component[object->object_id].object_id = ascii_character;
    object->component[COMP_MODEL] = object_model;

    ///////////////////// Primary Characteristics Component ///////////////////////////////

    Primary_Characteristics* primary;
    primary = (Primary_Characteristics *) malloc(sizeof(Primary_Characteristics));
    primary[ascii_character].object_id = ascii_character;

    model_component[object->object_id].object_id = ascii_character;
    object->component[COMP_MODEL] = object_model;

    //////////////////// Secondary Characteristics Component ////////////////////////////////

    Secondary_Characteristics* secondary;
    secondary = (Secondary_Characteristics *) malloc(sizeof(Secondary_Characteristics));
    secondary[ascii_character].object_id = ascii_character;

    model_component[object->object_id].object_id = ascii_character;
    object->component[COMP_MODEL] = object_model;

    //////////////////// Combat Stats Component ////////////////////////////////

    Combat_Stats* combat;
    combat = (Combat_Stats *) malloc(sizeof(Combat_Stats));
    combat[ascii_character].object_id = ascii_character;

    model_component[object->object_id].object_id = ascii_character;
    object->component[COMP_MODEL] = object_model;
    ///////////////////////////////////////////////////////////////////////////////////
}

void Object_Add_VAO(GLint data)  // TODO : these 2 functions should not exist !!!
{
    Vector_append(
        &vao_storage,
        data
    );
}
void Object_Add_VBO(GLint data) // TODO: see above
{
    Vector_append(
        &vbo_storage,
        data
    );
}

void Object_Cleanup()
{
    // delete all vao's that have been created
    printf(
        "Deleting VAO vectors: %d\n",
        Vector_size(&vao_storage)
    );

    for (int index = 0; index < Vector_size(&vao_storage); index++) {

        GLuint vao = Vector_get(
            &vao_storage,
            index
        );

        glDeleteVertexArrays(
            1,
            (GLuint *) &vao
        );
    }

    Vector_free_memory(&vao_storage);

// delete all vbo's that were created.

    printf(
        "Deleting VBO vectors: %d\n",
        Vector_size(&vbo_storage)
    );

    for (int index = 0; index < Vector_size(&vbo_storage); index++) {

        GLuint vbo = Vector_get(&vbo_storage, index);
        glDeleteBuffers(
            1,
            (GLuint *) &vbo
        );
    }

    Vector_free_memory(&vbo_storage);

    for(u32 index = 0; index < MAX_ENTITIES; index++){

        i32 object_id = game_entities->entity_id[index];


        for(u32 jay = 0; jay < COMP_COUNT; jay++){

            if(object[object_id].component[jay] != (void*)UNUSED &&
                object_id != UNUSED){

                free(
                    object[object_id].component[jay]
                );
            }
        }
    }
}
