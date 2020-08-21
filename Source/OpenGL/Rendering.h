//
// Created by frazor on 10/08/2020.
//

#ifndef SAND_ROGUE_RENDERING_H
#define SAND_ROGUE_RENDERING_H

#include "Source/OpenGL/Shaders.h"
#include "Source/Core/Game_Objects.h"
#include "Source/Core/Dungeon_Level.h"
#include "Source/Sand_Maths/Matrix_Utils.h"
#include "Source/Core/Sand_Vector.h"

void Render_all(
    Shader shader,
    Game_Model floor_model,
    mat4 projection_matrix,
    Current_Game_State current_game_state,
    vec3 light_position,
    vec3 light_color,
    Dungeon_Level_Current* dungeon_level_current
);

void Render_Model(
    i32 model,
    Shader shader
);


#endif //SAND_ROGUE_RENDERING_H
