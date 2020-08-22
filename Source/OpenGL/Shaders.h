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
#ifndef SHADERS_H
#define SHADERS_H

#include "Source/Common.h"
#include "Source/Core/Text_File_Utils.h"


Shader Load_Shader();

void check_shader_error(
    GLuint shader,
    GLuint flag,
    bool isProgram,
    const char *errorMessage
);


#endif // SHADERS_H
