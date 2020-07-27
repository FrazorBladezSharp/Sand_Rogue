//
// Created by frazor on 24/07/2020.
//

/*
###############################################################
# Project created by Frazor Sharp 2020 Jul 15
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
#include "Matrix_Utils.h"


Main_Camera Calc_Camera_View_Matrix(Main_Camera camera) {

    glm_mat4_identity(
        camera.view_matrix
    );

    glm_rotate_x(
        camera.view_matrix,
        glm_rad(camera.rotationX),
        camera.view_matrix
    );

    glm_rotate_y(
        camera.view_matrix,
        glm_rad(camera.rotationY),
        camera.view_matrix
    );

    glm_rotate_z(
        camera.view_matrix,
        glm_rad(camera.rotationZ),
        camera.view_matrix
    );

    glm_translate_x(
        camera.view_matrix,
        camera.position[0] * -1.0f
    );

    glm_translate_y(
        camera.view_matrix,
        camera.position[1] * -1.0f
    );

    glm_translate_z(
        camera.view_matrix,
        camera.position[2] * -1.0f
    );

    return camera;
}

Game_Model Calc_Model_matrix(Game_Model model,
                             vec3 position,
                             float rotationX,
                             float rotationY,
                             float rotationZ,
                             vec3 scale) {

    glm_mat4_identity(
        model.model_matrix
    );

    glm_translate_x(
        model.model_matrix,
        position[0]
    );

    glm_translate_y(
        model.model_matrix,
        position[1]
    );

    glm_translate_z(
        model.model_matrix,
        position[2]
    );

    glm_rotate_x(
        model.model_matrix,
        glm_rad(rotationX),
        model.model_matrix
    );

    glm_rotate_y(
        model.model_matrix,
        glm_rad(rotationY),
        model.model_matrix
    );

    glm_rotate_z(
        model.model_matrix,
        glm_rad(rotationZ),
        model.model_matrix
    );

    glm_scale(
        model.model_matrix,
        scale
    );

    return model;
}

