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
#include "Text_File_Utils.h"


char *Read_A_Text_File(const char *file) {

    /////////////// Read a text File ///////////////

    FILE *file_in = fopen(
        file,
        "r"
    );

    if (file_in == NULL) {

        return NULL;

    }

    ///////////// read file into a buffer ////////////////////

    char *buffer;                   // storage buffer in bytes
    long file_length;               // in bytes

    fseek(                         // set pointer to a location in file
        file_in,
        0L,                        // offset
        SEEK_END                   // go to end of file
    );

    file_length = ftell(           // gives end of file in bytes
        file_in
    );

    fseek(
        file_in,
        0L,
        SEEK_SET                  // go to start of file
    );

    buffer = (char *) calloc(        // allocates memory
        file_length + 1,               // file_length amount
        sizeof(char)               // in bytes
    );

    if (buffer == NULL) {
        return NULL;
    }

    fread(               // read all of file from current position
        buffer,
        sizeof(char),
        file_length,
        file_in
    );

    ///////////// Close file when finished ////////////

    fclose(
        file_in
    );

    return buffer;      // return the contents of the file.
}