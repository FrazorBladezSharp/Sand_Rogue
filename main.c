
/** @file Main This is Prototype Code
 * TODO : finish current todo's

 * TODO : healing injuries
 * TODO : spell mechanics & ranged attacks (Targeting) ???
 * TODO : Traps
 * TODO : Line Of Sight and lighting (add / remove render_models)
 * TODO : MAX_LEVELS = 26
 * TODO : stairs down and Victory Conditions
 * TODO : Graphical User Interface.
 * TODO : Backpack / Equipment
 * TODO : Missing features.
###############################################################
# Project created by Frazor Sharp 2020 Jul 22
#
# Sand_Rogue for C (11) Version 0.1
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

#include "Source/OpenGL/Sand_Window_3D.h"
#include "Source/OpenGL/Shaders.h"
#include "Source/Core/Game_Objects.h"
#include  "Source/Core/Main_Game_Loop.h"

int
/** The run time entry point for Sand_Rogue
 * @return 0 = all ok.
 */
main() {

    printf(
        "Startup = %d\nWelcome to Sand_Rogue !\n\n",
        true
    );

    // window openGL - NOTE : must be done first to get the openGL context.
    SDL_Window* window = Sand_Window_Create();

    Object_Initialize();
    Game_Items_Initialize();

    //////////////////// Shader /////////////////////////////////

    Shader shader = Load_Shader();

    ///////////////// Main Game Loop ////////////////////////////

    Main_Game_Loop(
        shader,
        window
    );

    //////////////////// Clean up and Exit ////////////////////////////

    // cleanup OpenGL - anything stored on the gfx card.

    glDeleteProgram(
        shader.shader_program
    );

    Dungeon_Level_Cleanup();
    Object_Cleanup();

    Sand_Window_Destroy(window);

    return 0;
}
