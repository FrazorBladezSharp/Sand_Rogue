//
// Created by frazor on 24/07/2020.
//

/*
###############################################################
# Project created by Frazor Sharp 2020 Jul 24
#
# Sandbox for C / C++ Version 0.1
#
# Contact email         : frazor.sharp@virginmedia.com
# Website               : none
# Twitch                : FrazorBladezSharp
# Youtube               : Frazor Sharp
#
# All code is free to use as you please
# Please be aware this file is provided by Qt
# Open Source licence   : doc.qt.io/qt-5/opensourcelicence.html
###############################################################
*/
#include "Shaders.h"


Shader Load_Shader() {

    const char *vertex_shader_source = Read_A_Text_File(
        "Resource/GLSL/Color_Vertex.shader"
    );

    if (vertex_shader_source == NULL){

        printf("Vertex Shader failed to load.\n");
    }

    const char *fragment_shader_source = Read_A_Text_File(
        "Resource/GLSL/Color_Fragment.shader"
    );

    if (fragment_shader_source == NULL){

        printf("Fragment Shader failed to load.\n");
    }

    GLuint shader_program = glCreateProgram();

    GLuint vertex_shader = glCreateShader(
        GL_VERTEX_SHADER
    );

    GLuint fragment_shader = glCreateShader(
        GL_FRAGMENT_SHADER
    );

    const GLint shader_vertex_source_length = strlen(
        vertex_shader_source
    );

    glShaderSource(
        vertex_shader,
        1,
        (const GLchar *const *) &vertex_shader_source,
        &shader_vertex_source_length
    );

    glCompileShader(
        vertex_shader
    );

    check_shader_error(
        vertex_shader,
        GL_COMPILE_STATUS,
        false,
        "Error : glCompileShader failed. "
    );

    glAttachShader(
        shader_program,
        vertex_shader
    );

    const GLint shader_fragment_source_length = strlen(
        fragment_shader_source
    );

    glShaderSource(
        fragment_shader,
        1,
        (const GLchar *const *) &fragment_shader_source,
        &shader_fragment_source_length
    );

    glCompileShader(
        fragment_shader
    );

    check_shader_error(
        fragment_shader,
        GL_COMPILE_STATUS, false,
        "Error : glCompileShader failed. "
    );

    glAttachShader(
        shader_program,
        fragment_shader
    );

    glLinkProgram(
        shader_program
    );

    glValidateProgram(
        shader_program
    );

    glUseProgram(
        shader_program
    );

    free(
        (void*)vertex_shader_source
    );

    free(
        (void*)fragment_shader_source
    );

    Shader current_shader = {

        .shader_program = shader_program,
        .uniform_Locations[0] = glGetUniformLocation(
            shader_program,
            "model_matrix"
        ),

        .uniform_Locations[1] = glGetUniformLocation(
            shader_program,
            "view_matrix"
        ),

        .uniform_Locations[2] = glGetUniformLocation(
            shader_program,
            "projection_matrix"
        ),

        .uniform_Locations[3] = glGetUniformLocation(
            shader_program,
            "light_position"
        ),

        .uniform_Locations[4] = glGetUniformLocation(
            shader_program,
            "light_color"
        ),

        .uniform_Locations[5] = glGetUniformLocation(
            shader_program,
            "shine_damper"
        ),

        .uniform_Locations[6] = glGetUniformLocation(
            shader_program,
            "reflectivity"
        ),

        .uniform_Locations[7] = glGetUniformLocation(
            shader_program,
            "sky_color"
        ),

        .uniform_Locations[8] = glGetUniformLocation(
            shader_program,
            "camera_position"
        ),
    };

    return current_shader;
}

void check_shader_error(
    GLuint shader,
    GLuint flag,
    bool isProgram,
    const char *errorMessage){

    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram) {
        glGetProgramiv(
            shader,
            flag,
            &success
        );

    } else {

        glGetShaderiv(
            shader,
            flag,
            &success
        );
    }

    if (success == GL_FALSE) {
        if (isProgram) {
            glGetProgramInfoLog(
                shader,
                sizeof(error),
                NULL,
                error
            );

        } else {

            glGetShaderInfoLog(
                shader,
                sizeof(error),
                NULL,
                error
            );
        }

        printf(
            "%s : %s\n",
            errorMessage,
            error
        );
    }
}
