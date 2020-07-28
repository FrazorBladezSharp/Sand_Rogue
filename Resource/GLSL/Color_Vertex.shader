#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform vec3 light_position;
uniform vec3 light_color;
uniform float shine_damper;     // roughness of surface low = rough
uniform float reflectivity;     // cloth = low// metal = med to high // water glass high //
uniform vec3 sky_color;
uniform vec3 camera_position;

const float density = 0.05f;
const float gradient = 1.5f;

out vec4 v_out_color;

void main()
{


    vec3 model_position = vec3(
        model_matrix * vec4(
            position,
            1.0f
        )
    );

    vec4 delta_camera = view_matrix * vec4(model_position, 1.0f);

    gl_Position =   projection_matrix * delta_camera;

    /////////////////////////////// Lighting ///////////////////////////////

    vec3 unitNormal = normalize(
        vec3(model_matrix * vec4(normal, 0.0f))
    );


    vec3 unitLightVector = normalize(
        light_position - model_position
    );

    vec3 unitVectorToCamera = normalize(
        vec3(
            inverse(view_matrix) * vec4(0.0f, 0.0f, 0.0f, 1.0f)
        ) - model_position
    );

    // Phong Lighting Equations
    // Ambient lighting : background light

    vec3 ambientLight = sky_color;

    // diffuse Light : direct light from a Source.

    float lightIntensity = dot(
        unitLightVector,
        unitNormal
    );

    vec3 diffuseLight = lightIntensity * light_color;

    // specular light : how much light is directly reflected to the camera.

    vec3 reflectedLightDirection = reflect(
        -unitLightVector,
        unitNormal
    );

    float specularFactor = dot(
        reflectedLightDirection,
        unitVectorToCamera
    );

    float dampedFactor = pow(
        specularFactor,
        shine_damper
    );

    vec3 specularLight = dampedFactor * reflectivity * light_color;

    // Final Lighting

    vec4 lighting = vec4(
        clamp(specularLight, 0.01f, 1.0f) +
        clamp(diffuseLight, 0.01f, 1.0f) +
        clamp(ambientLight, 0.01f, 1.0f),
        1.0f
    );

    // Fog
    float distanceToCamera = length(
        delta_camera.xyz
    );

    float v_Visibility = exp(
        -pow(
            distanceToCamera * density,
            gradient
        )
    );

    v_Visibility = clamp(
        v_Visibility,
        0.0f,
        1.0f
    );


    // maybe we should clamp the final lighting value ???
    // or leave to get a color saturation ie Blinding light !
    // as this is in the Vertex Shader it Should cause
    // Faceting which is intended for this application.

    v_out_color = mix(
        vec4(sky_color, 1.0f),
        lighting * color,
        v_Visibility
    );
}
