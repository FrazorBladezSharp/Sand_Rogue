//
// Created by frazor on 10/08/2020.
//

#include "Rendering.h"

void Render_all(
    Shader shader,
    Game_Model floor_model,
    mat4 projection_matrix,
    Current_Game_State current_game_state,
    vec3 light_position,
    vec3 light_color,
    Dungeon_Level_Current* dungeon_level_current,
    Vector* render_models)
{
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    glUseProgram(
        shader.shader_program
    );

    glBindVertexArray(                          // set which VAO to draw
        floor_model.vaoID
    );

    glUniformMatrix4fv(
        shader.uniform_Locations[UNIFORM_LOC_PROJECTION_MATRIX],
        1,
        GL_FALSE,
        (float *) projection_matrix
    );

    glUniformMatrix4fv(
        shader.uniform_Locations[UNIFORM_LOC_VIEW_MATRIX],
        1,
        GL_FALSE,
        (float *) current_game_state.main_camera.view_matrix
    );

    glUniform3f(
        shader.uniform_Locations[UNIFORM_LOC_LIGHT_POSITION],
        light_position[0],
        light_position[1],
        light_position[2]
    );

    glUniform3f(
        shader.uniform_Locations[UNIFORM_LOC_LIGHT_COLOR],
        light_color[0],
        light_color[1],
        light_color[2]
    );

    float shine_damper = 8.0f;

    glUniform1f(
        shader.uniform_Locations[UNIFORM_LOC_SHINE_DAMPER],
        shine_damper
    );                          // roughness of surface low = rough

    float reflectivity = 1.0f; // % cloth = low// metal = med to high // water glass high //

    glUniform1f(
        shader.uniform_Locations[UNIFORM_LOC_REFLECTIVITY],
        reflectivity
    );

    vec3 sky_color;         // Yay Magic numbers for the Win !

    sky_color[0] = 0.05f;
    sky_color[1] = 0.02f;
    sky_color[2] = 0.01f;

    glUniform3f(
        shader.uniform_Locations[UNIFORM_LOC_SKY_COLOR],
        sky_color[0],
        sky_color[1],
        sky_color[2]
    );

    glUniform3f(
        shader.uniform_Locations[UNIFORM_LOC_CAMERA_POSITION],
        current_game_state.main_camera.position[0],
        current_game_state.main_camera.position[1],
        current_game_state.main_camera.position[2]
    );

    //////////////////////// Render Dungeon Map //////////////////////////

    for (u8 x = 0; x <= MAP_WIDTH; x++) {

        for (u8 z = 0; z <= MAP_HEIGHT; z++) {

            if (dungeon_level_current->map_cells[x][z]) {

                vec3 floor_position = {(float) x, 0.0f, (float) z};

                Position current_floor_position = {
                    0,
                    floor_position[0],
                    floor_position[1],
                    floor_position[2],
                    0.0f,
                    0.0f,
                    0.0f,
                    1.0f
                };

                floor_model = Calc_Model_matrix(
                    floor_model,
                    &current_floor_position
                );

                glUniformMatrix4fv(
                    shader.uniform_Locations[UNIFORM_LOC_MODEL_MATRIX],
                    1,
                    GL_FALSE,
                    (float *) floor_model.model_matrix
                );

                glDrawElements(                               // draw using Triangles
                    GL_TRIANGLES,
                    floor_model.num_indices,
                    GL_UNSIGNED_INT,
                    (void *) 0
                );
            }
        }
    } // end of map render

    for(i32 index = 0; index < Vector_Size(render_models); index++){

        Render_Model(Vector_Get(render_models, index), shader);
    }

    glBindVertexArray(                          // disable the used VAO
        0
    );
} // end of render all

    ////////////////////////// Render Model //////////////////////////////////////////////

void Render_Model(
    i32 model,
    Shader shader){

    Game_Model* game_model = Object_Lookup_Component(model, COMP_MODEL);
    Position* position = Object_Lookup_Component(model, COMP_POSITION);

    glBindVertexArray(                          // set which VAO to draw
        game_model->vaoID
    );

    *game_model = Calc_Model_matrix(
        *game_model,
        position
    );

    glUniformMatrix4fv(
        shader.uniform_Locations[UNIFORM_LOC_MODEL_MATRIX],
        1,
        GL_FALSE,
        (float *) game_model->model_matrix
    );

    glDrawElements(                               // draw using Triangles
        GL_TRIANGLES,
        game_model->num_indices,
        GL_UNSIGNED_INT,
        (void *) 0
    );
}
