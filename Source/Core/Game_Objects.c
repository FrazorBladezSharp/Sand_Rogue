//
// Created by frazor on 29/07/2020.
//

#include "Game_Objects.h"

Vector vao_storage;
Vector vbo_storage;
Game_Entities game_entities;

void Object_Initialize(Game_Object player)
{
    Vector_init(&vao_storage);
    Vector_init(&vbo_storage);


    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize Entities
        game_entities.entity_id[index] = UNUSED;            // set all entities to unused
    }

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // find an unused entity slot
        if (game_entities.entity_id[index] == UNUSED) {       // initialize player
            game_entities.entity_id[index] = index;         // register player as an entity
            player.object_id = index;                      // assign the player an entity id
            break;
        }
    }

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize components
        g_position_component[index].object_id = UNUSED;
        g_model_component[index].object_id = UNUSED;
    }

}

Game_Object Object_Create()
{
    Game_Object player;
    Position *player_position;
    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // find an unused entity slot
        if (game_entities.entity_id[index] == UNUSED) {       // initialize player
            game_entities.entity_id[index] = index;         // register player as an entity
            player.object_id = index;                      // assign the player an entity id
            break;
        }
    }

    for (u32 index = 0; index < MAX_ENTITIES; index++) {      // initialize components
        g_position_component[index].object_id = UNUSED;
        g_model_component[index].object_id = UNUSED;
    }

    // NOTE: you must free the memory before game exit      *** NOTE ****

    player_position = (Position *) malloc(
        sizeof(Position)
    );

    player_position->object_id = player.object_id;         // set values for the player position.
    player_position->position[0] = 0.0f;                   // initialize all to zero
    player_position->position[1] = 0.5f;
    player_position->position[2] = 0.0f;
    player_position->rotationX = 0.0f;
    player_position->rotationY = 45.0f;
    player_position->rotationZ = 0.0f;
    player_position->scale = 1.0f;

    vec4 player_color;
    player_color[0] = 0.1f;
    player_color[1] = 0.5f;
    player_color[2] = 0.1f;
    player_color[3] = 1.0f;

    Game_Model *player_model;
    player_model = (Game_Model *) malloc(sizeof(Game_Model));

    player_model = Load_Model_3D(
        "Resource/Models/Player.obj",
        player_color,
        &vao_storage,
        &vbo_storage,
        player_model
    );

    player_model->object_id = player.object_id;

    player.component[COMP_POSITION] = player_position;     // add position component to player
    player.component[COMP_MODEL] = player_model;

    g_position_component[player.object_id].object_id =     // keep track of all position components
        player.object_id;
    g_model_component[player.object_id].object_id =
        player.object_id;

    return player;
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

void Object_Cleanup(Game_Object player)
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

    free(player.component[COMP_POSITION]);
    free(player.component[COMP_MODEL]);
}
