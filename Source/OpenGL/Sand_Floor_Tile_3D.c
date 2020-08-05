//
// Created by frazor on 30/07/2020.
//

#include "Sand_Floor_Tile_3D.h"

Game_Model Sand_Floor_Tile_3D_Create(SDL_Window* window)
{
    SDL_GL_MakeCurrent(window, SDL_GL_GetCurrentContext());

    GLfloat vertex_array[] = {
        -0.5f, 0.0f, -0.5f, // v0 far left
        -0.5f, 0.0f, 0.5f, // v1 near left
        0.5f, 0.0f, 0.5f, // v2 near right
        0.5f, 0.0f, -0.5f  // v3 far right
    };

    GLfloat color_array[] = {
        0.5f, 0.1f, 0.5f, 1.0f,
        0.4f, 0.4f, 0.4f, 1.0f,
        0.5f, 0.1f, 0.5f, 1.0f,
        0.4f, 0.4f, 0.4f, 1.0f
    };

    GLfloat normal_array[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    GLuint index_array[] = {
        0, 1, 2,             // triangle 0
        0, 2, 3              // triangle 1
    };

    GLuint vaoID;

    glCreateVertexArrays(
        1,
        &vaoID
    );

    Object_Add_VAO(vaoID);

    glBindVertexArray(                          // bind the VAO to record what we do
        vaoID
    );

    /////////////////////////// Index Buffer ////////////////////////////////////

    u32 iboID;                              // Index Buffer Object for our Indices

    glGenBuffers(
        1,
        &iboID
    );

    Object_Add_VBO(iboID);

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        iboID
    );

    glBufferData(                           // send our data to the Gfx Card
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(index_array),
        &index_array[0],
        GL_STATIC_DRAW
    );

    /////////////////////////////// Vertex Buffer ///////////////////////////////////////////////

    GLuint vboID;                                  // Vertex Buffer Object for the vertices

    glGenBuffers(
        1,
        &vboID
    );

    Object_Add_VBO(vboID);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        vboID
    );

    glBufferData(                               // send our data to the gfx card
        GL_ARRAY_BUFFER,
        sizeof(vertex_array),
        &vertex_array[0],
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,                  // attribute must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,                  // stride
        (void *) 0            // array buffer offset
    );

    glEnableVertexAttribArray(
        0
    );

    /////////////////////////// Color Buffer /////////////////////////////////////////

    GLuint color_buffer;                                  // Vertex Buffer Object for the vertices

    glGenBuffers(
        1,
        &color_buffer
    );

    Object_Add_VBO(color_buffer);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        color_buffer
    );

    glBufferData(                               // send our data to the gfx card
        GL_ARRAY_BUFFER,
        sizeof(color_array),
        &color_array[0],
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        1,                  // attribute must match the layout in the shader.
        4,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,                  // stride
        (void *) 0            // array buffer offset
    );

    glEnableVertexAttribArray(
        1
    );

    /////////////////////////// Normals Buffer /////////////////////////////////////////

    GLuint nboID;                                  // Vertex Buffer Object for the vertices

    glGenBuffers(
        1,
        &nboID
    );

    Object_Add_VBO(nboID);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        nboID
    );

    glBufferData(                               // send our data to the gfx card
        GL_ARRAY_BUFFER,
        sizeof(normal_array),
        &normal_array[0],
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        2,                  // attribute must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_TRUE,           // normalized
        0,                  // stride
        (void *) 0            // array buffer offset
    );

    glEnableVertexAttribArray(
        2
    );

    Game_Model floor = {
        .vaoID = vaoID,
        .num_indices = sizeof(index_array),
        .object_id = UNUSED,
    };

    /////////////////// Unbind the buffers ////////////////////

    glBindVertexArray(                      // disable our VAO
        0
    );

    glBindBuffer(                           // disable our VBO
        GL_ELEMENT_ARRAY_BUFFER,
        0
    );

    glBindBuffer(                           // disable oud IBO
        GL_ARRAY_BUFFER,
        0
    );

    return floor;
}