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
#ifndef SAND_DICE_H
#define SAND_DICE_H

#include "Common.h"


static void Dice_Initialize() {
    srand((uint) time(NULL));
}

static int Dice_Roll(int num, int type) {
    int ret = 0;
    for (int i = 0; i < num; i++) ret += (rand() % type) + 1;
    return ret;
}

// using a 3d6 system we have the following :

static bool Dice_Critical_Success(int effectiveSkill, int diceRoll) {
    bool ret = false;
    int crit = 4;
    if (effectiveSkill > 20) effectiveSkill = 20;
    if (effectiveSkill > 14) crit += (effectiveSkill - 14);
    if (diceRoll <= crit) ret = true;
    return ret;
}

static bool Dice_Critical_Failure(int effectiveSkill, int diceRoll) {
    bool ret = false;
    if (effectiveSkill > 20) effectiveSkill = 20;
    if (effectiveSkill < 3) effectiveSkill = 3;
    if (diceRoll == 18) ret = true;
    else if ((diceRoll == 17) && (effectiveSkill < 16)) ret = true;
    else if (diceRoll >= effectiveSkill + 10) ret = true;
    return ret;
}


#endif // SAND_DICE_H