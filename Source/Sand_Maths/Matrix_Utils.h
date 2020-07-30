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
#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <cglm/cglm.h>
#include "Source/Common.h"


Main_Camera Calc_Camera_View_Matrix(Main_Camera camera);

Game_Model Calc_Model_matrix(Game_Model model,
                             Position* current_position
);


#endif // MATRIX_UTILS_H
