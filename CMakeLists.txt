cmake_minimum_required(VERSION 3.16)
project(Sand_Rogue C)

set(CMAKE_C_STANDARD 11)

include_directories(
        ./
        /usr/include
        /usr/local/include
)

add_executable(
        Sand_Rogue main.c
        Source/Core/Text_File_Utils.c
        Source/Core/Text_File_Utils.h
        Source/OpenGL/Shaders.c
        Source/OpenGL/Shaders.h
        Source/Sand_Maths/Matrix_Utils.c
        Source/Sand_Maths/Matrix_Utils.h
        Source/Common.h
        Source/Sand_Dice.h
        Source/Core/Map.c
        Source/Core/Map.h
        Source/OpenGL/Load_Model_3D.c
        Source/OpenGL/Load_Model_3D.h
        Source/Core/Sand_Vector.c
        Source/Core/Sand_Vector.h
        Source/Core/Game_Objects.c
        Source/Core/Game_Objects.h
        Source/OpenGL/Sand_Window_3D.c
        Source/OpenGL/Sand_Window_3D.h
        Source/OpenGL/Sand_Floor_Tile_3D.c
        Source/OpenGL/Sand_Floor_Tile_3D.h
        Source/Core/Main_Game_Loop.c
        Source/Core/Main_Game_Loop.h
        Source/Graphical_User_Interface/User_Input.c
        Source/Graphical_User_Interface/User_Input.h
        Source/GURPS/Sand_Combat.c
        Source/GURPS/Sand_Combat.h
        Source/GURPS/Sand_Damage.c Source/GURPS/Sand_Damage.h)

target_link_libraries(
        Sand_Rogue SDL2 GLEW GL assimp m
)

link_directories(
        /usr/local/lib
)
