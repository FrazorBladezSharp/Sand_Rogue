//
// Created by frazor on 26/07/2020.
//

#include "Load_Model_3D.h"

Game_Model* Load_Model_3D(const char* path, vec4 color,
                        Vector *vao_storage, Vector *vbo_storage,
                        Game_Model* loaded_asset)
{
    loaded_asset->vaoID = 0;
    loaded_asset->num_indices = 0;

    const C_STRUCT aiScene* scene = NULL;

    scene = aiImportFile(
        path,
        aiProcessPreset_TargetRealtime_Quality
    );

    assert(scene != NULL);

    //////////////// Setup VAO /////////////////////////////

    GLuint vao_buffer = GL_FALSE;

    glGenVertexArrays(
        1,
        &vao_buffer
    );


    Vector_append(
        vao_storage,
        vao_buffer
    );

    glBindVertexArray(
        vao_buffer
    );

    /////////////////// Xfer indices /////////////////////////////////

    // get our mesh from the scene.
    const struct aiMesh* mesh = scene->mMeshes[0];

    // create an array to store face indices
    uint* face_array;

    face_array = (uint*) malloc(
        sizeof(uint) * mesh->mNumFaces * 3
    );

    uint face_index = 0;

    // copy face indices from mesh to face_array.
    // these are stored as array of aiFace = 3 indices
    for(uint i = 0; i < mesh->mNumFaces; i++)
    {
        const struct aiFace* face = &mesh->mFaces[i];

        memcpy(
            &face_array[face_index],
            face->mIndices,
            3 * sizeof(uint)
        );

        face_index += 3;
    }

    GLuint index_buffer;

    glGenBuffers(
        1,
        &index_buffer
    );

    Vector_append(
        vbo_storage,
        index_buffer
    );

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        index_buffer
    );

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(uint) * mesh->mNumFaces * 3,
        face_array,
        GL_STATIC_DRAW
    );

    ///////// Xfer Vertices ///////

    uint vertex_buffer;

    glGenBuffers(
        1,
        &vertex_buffer
    );

    Vector_append(
        vbo_storage,
        vertex_buffer
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        vertex_buffer
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * 3 * mesh->mNumVertices,
        mesh->mVertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glEnableVertexAttribArray(
        0
    );

    ////// Create and Xfer colors ////////////

    float* colors_array;

    colors_array = (float*) malloc(
        sizeof(float) * mesh->mNumFaces * 3 * 4
    );

    uint i = 0;

    while( i <  mesh->mNumFaces * 3 * 4 )
    {
        colors_array[i] = color[0];
        i +=1;
        colors_array[i] = color[1];
        i +=1;
        colors_array[i] = color[2];
        i +=1;
        colors_array[i] = color[3];
        i +=1;
    }

    uint color_buffer;

    glGenBuffers(
        1,
        &color_buffer
    );

    Vector_append(
        vbo_storage,
        color_buffer
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        color_buffer
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * mesh->mNumFaces * 3 * 4,
        colors_array,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer( // this requires a shader.
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glEnableVertexAttribArray(
        1
    );

    ///////// Xfer Normals ///////

    uint normal_buffer;

    glGenBuffers(
        1,
        &normal_buffer
    );

    Vector_append(
        vbo_storage,
        normal_buffer
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        normal_buffer
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * 3 * mesh->mNumVertices,
        mesh->mNormals,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_TRUE,
        0,
        (void*)0
    );

    glEnableVertexAttribArray(
        2
    );

    //////////////////////////////

    loaded_asset->vaoID = vao_buffer;
    loaded_asset->num_indices = face_index;

    // 	/* cleanup - calling 'aiReleaseImport' is important, as the library
    //   keeps internal resources until the scene is freed again. Not
    //   doing so can cause severe resource leaking. */
    aiReleaseImport(scene);

    /* We added a log stream to the library, it's our job to disable it
       again. This will definitely release the last resources allocated
       by Assimp.*/
    //aiDetachAllLogStreams();

    free(face_array);
    free(colors_array);

    return loaded_asset;
}
