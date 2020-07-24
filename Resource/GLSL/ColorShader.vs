#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;


out vec4 v_color;

void main()
{
    v_color = color;

    gl_Position =   projection_matrix *
                    view_matrix *
                    model_matrix *
                    vec4(position, 1.0f
    );
}
