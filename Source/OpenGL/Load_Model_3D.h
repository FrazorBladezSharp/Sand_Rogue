//
// Created by frazor on 26/07/2020.
//

#ifndef SAND_ROGUE_LOAD_MODEL_3D_H
#define SAND_ROGUE_LOAD_MODEL_3D_H

#include "Source/Common.h"
#include "Source/Core/Sand_Vector.h"

Game_Model* Load_Model_3D(const char* path, vec4 color,
                          Vector *vao_storage, Vector *vbo_storage,
                          Game_Model* player_model);

#endif //SAND_ROGUE_LOAD_MODEL_3D_H
