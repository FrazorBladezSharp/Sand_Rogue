
/** @file Main This is Prototype Code
 * TODO: think about if statements as they can be taken out
 * eg a * ( condition for a ) + b * ( condition for b ) + etc ...
 *
###############################################################
# Project created by Frazor Sharp 2020 Jul 22
#
# Sand_Rogue for C / C++ Version 0.1
#
# Contact email         : frazor.sharp@virginmedia.com
# Github                : https://github.com/FrazorBladezSharp/Sand_Rogue
# Twitch                : FrazorBladezSharp
# Youtube               : Frazor Sharp
#
# All code is free to use as you please
# free for all Licence !
###############################################################
*/

#include "Source/Common.h"
#include "Source/OpenGL/Sand_Window_3D.h"

#include "Source/Sand_Dice.h"
#include "Source/Core/Text_File_Utils.h"
#include "Source/OpenGL/Shaders.h"

#include "Source/Core/Game_Objects.h"
//#include "Source/OpenGL/Sand_Floor_Tile_3D.h"
//#include "Source/Core/Map.h"

//#include  "Source/Core/Main_Game_Loop.h"

int
/** The run time entry point for Sand_Rogue
 * @return 0 = all ok.
 */
main() {

    printf(
        "Welcome to Sand_Rogue !\n\n"
    );

    // window openGL - NOTE : must be done first to get the openGL context.
    SDL_Window* window = Sand_Window_Create();

    Object_Initialize();

    //Game_Model floor = Sand_Floor_Tile_3D_Create();

//    ////////////////////////////////////// define the Player ////////////////////////////
//
//    Position *player_position;
//    Position *monster_position;
//
//    Game_Model *player_model;
//    Game_Model
//
//    player_position = player.component[COMP_POSITION];
//    monster_position = monster.component[COMP_POSITION];
//    player_model = player.component[COMP_MODEL];
//    monster_model = monster.component[COMP_MODEL];

    //////////////////////////// Create a Dungeon Level///////////////////////////////

    Dice_Initialize();

    // create Dungeon Level - can be done anytime before main game loop
    i8 dungeon_level = 1;

    Dungeon_Level_Current *dungeon_level_current;

    dungeon_level_current = (Dungeon_Level_Current *) malloc(sizeof(Dungeon_Level_Current));

    dungeon_level_current->dungeon_level = dungeon_level;
    // set all locations to false.
    for (int x = 0; x <= MAP_WIDTH; x++) {
        for (int y = 0; y <= MAP_HEIGHT; y++) {
            dungeon_level_current->map_cells[x][y] = false;
        }
    }

  //  dungeon_level_current = Map_Create_Dungeon_Level(
 //       dungeon_level_current,
 //       player.component[COMP_POSITION]                     // we set player position as a side effect of the function
 //   );

//    monster_position->position[0] += player_position->position[0] + 1.0f;
//    monster_position->position[2] += player_position->position[2] + 1.0f;

    //////////////////// Shader /////////////////////////////////

    GLint shader = Load_Shader();

    ///////////////// Main Game Loop ////////////////////////////

//    Main_Game_Loop(
//        shader,
//        player_position,
//        monster_position,
//        dungeon_level_current,
//        floor,
//        player_model,
//        monster_model,
//        window
//    );

    //////////////////// Clean up and Exit ////////////////////////////

    // cleanup OpenGL - anything stored on the gfx card.

    glDeleteProgram(
        shader
    );

//    free(
//        dungeon_level_current
//    );

    Object_Cleanup();

    Sand_Window_Destroy(window);

    return 0;
}
