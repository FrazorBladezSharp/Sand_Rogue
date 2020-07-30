//
// Created by frazor on 29/07/2020.
//

#include "Game_Objects.h"

static Vector vao_storage;
static Vector vbo_storage;

static Game_Object object[MAX_ENTITIES];
static Game_Entities game_entities[MAX_ENTITIES];

void Object_Initialize()
{
    Vector_init(&vao_storage);
    Vector_init(&vbo_storage);


    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize Entities
        game_entities->entity_id[index] = UNUSED;            // set all entities to unused
        object->object_id = UNUSED;
    }

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize components
        g_position_component[index].object_id = UNUSED;
        g_model_component[index].object_id = UNUSED;
    }
}

Game_Object Object_Create()
{
    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // find an unused entity slot
        if (game_entities->entity_id[index] == UNUSED) {       // initialize object
            game_entities->entity_id[index] = index;         // register object as an entity
            object[index].object_id = index;                      // assign the object an entity id
            break;
        }
    }

    Position *object_position;
    Game_Model *object_model;

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize components
        g_position_component[index].object_id = UNUSED;
        g_model_component[index].object_id = UNUSED;
    }

    // NOTE: you must free the memory before game exit      *** NOTE ****

    object_position = (Position *) malloc(
        sizeof(Position)
    );

    object_position->object_id = object->object_id;         // set values for the object position.
    object_position->position[0] = 0.0f;                   // initialize all to zero
    object_position->position[1] = 0.5f;
    object_position->position[2] = 0.0f;
    object_position->rotationX = 0.0f;
    object_position->rotationY = -45.0f;
    object_position->rotationZ = 0.0f;
    object_position->scale = 1.0f;

    vec4 object_color;              // TODO : move to function definition.
    object_color[0] = 0.1f;
    object_color[1] = 0.5f;
    object_color[2] = 0.1f;
    object_color[3] = 1.0f;


    object_model = (Game_Model *) malloc(sizeof(Game_Model));
    object_model = Load_Model_3D(
        "Resource/Models/Player.obj",
        object_color,
        &vao_storage,
        &vbo_storage,
        object_model
    );

    object->component[COMP_POSITION] = object_position;     // add position component to object
    object->component[COMP_MODEL] = object_model;

    g_position_component[object->object_id].object_id =     // keep track of all position components
        object->object_id;
    g_model_component[object->object_id].object_id =
        object->object_id;

    return *object; // TODO: return the object id not a full copy !
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
