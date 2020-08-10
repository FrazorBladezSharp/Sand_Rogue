//
// Created by frazor on 10/08/2020.
//

#include "Items_Fixtures.h"

// TODO: Initialize Models
void Items_Initialize_Models()
{
// armour  as above location  93          ]       object cycle through objects to place them
// weapon as above location   41          )       object
// rings  as above             61          =       object
// potions : as above location 33          !       object
// rods & staves  as above     47          /       object
// scrolls  as above           63          ?       object
// food  as above              58          :       object

// gold  as above              42          *  #define GOLD_CALC (rnd(50 + 10 * level) + 2)
// chance per room ((rnd(3) == 3) && (! has not seen amulet || (level >= max_level))) thing = gold
// stairs down  as above       62          >       thing
// stairs up  as above         60          <       thing
// Trap  as above              94          ^       thing
// Doors  as above            43          +       thing

}

void Items_Add_To_Level()
{
    // TODO: Add Fixtures to Level
// stairs down  as above       62          >       thing
// stairs up  as above         60          <       thing
// Trap  as above              94          ^       thing
// Doors  as above            43          +       thing
}

void Items_Add_to_Room()
{
    // TODO: add room Contents when door is opened
// Room_Contents. room_contents[index] room = dark (rnd(10) < (level - 1))
// MAX CONTENTS PER LEVEL max things = num rooms  max objects = num_rooms
// things = stairs doors gold & objects
// objects = items 35% per max_object then pick random object
// items & location

// chance per room (rnd(100) < (gold value > 0 ? 80 : 25))

// armour as above location  93          ]       object cycle through objects to place them
// weapon  as above location   41          )       object
// rings  as above             61          =       object
// potions  as above location 33          !       object
// rods & staves  as above     47          /       object
// scrolls  as above           63          ?       object
// food  as above              58          :       object

// gold  as above              42          *  #define GOLD_CALC (rnd(50 + 10 * level) + 2)
// chance per room ((rnd(3) == 3) && (! has not seen amulet || (level >= max_level))) thing = gold


}
