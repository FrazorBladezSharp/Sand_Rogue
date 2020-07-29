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


    vec4 model_position = model_matrix * vec4(
            position,
            1.0f
    );

    vec4 delta_camera = view_matrix * model_position;

    gl_Position =   projection_matrix * delta_camera;

    /////////////////////////////// Lighting ///////////////////////////////

    vec3 surface_normal =  vec3(model_matrix * vec4(normal, 0.0f));
    vec3 to_light_vector = light_position - model_position.xyz;

    vec3 unit_normal = normalize(
        surface_normal
    );


    vec3 unit_light_vector = normalize(
        to_light_vector
    );

    vec3 to_camera_position =
        (inverse(view_matrix) *
        vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz -
        model_position.xyz;

    vec3 unit_vector_to_camera = normalize(
        to_camera_position
    );

    vec3 light_direction = - unit_light_vector;

    // Phong Lighting Equations
    // Ambient lighting : background light

    vec3 ambient_light = sky_color;

    // diffuse Light : direct light from a Source.

    float light_intensity = dot(
        unit_normal,
        unit_light_vector
    );

    float brightness = max(
        light_intensity,
        0.0f
    );

    vec3 diffuse_light = brightness * light_color;

    // specular light : how much light is directly reflected to the camera.

    vec3 reflected_light_direction = reflect(
        light_direction,
        unit_normal
    );

    float specular_factor = dot(
        reflected_light_direction,
        unit_vector_to_camera
    );

    specular_factor = max(
        specular_factor,
        0.0f
    );

    float damped_factor = pow(
        specular_factor,
        shine_damper
    );

    vec3 specular_light = damped_factor * reflectivity * light_color;

    // Final Lighting

    vec4 lighting = vec4(
        clamp(specular_light, 0.01f, 1.0f) +
        clamp(diffuse_light, 0.01f, 1.0f) +
        clamp(ambient_light, 0.01f, 1.0f),
        1.0f
    );

    // Fog
    float distance_to_camera = length(
        delta_camera.xyz
    );

    float visibility = exp(
        -pow(
            distance_to_camera * density,
            gradient
        )
    );

    visibility = clamp(
        visibility,
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
        visibility
    );
}
