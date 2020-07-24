cmake_minimum_required(VERSION 3.16)
project(Sand_Rogue C)

set(CMAKE_C_STANDARD 11)

include_directories(
        ./
        /usr/include
        ../libs/cglm-master/include
)

add_executable(
        Sand_Rogue main.c
        Source/Core/Text_File_Utils.c Source/Core/Text_File_Utils.h)

target_link_libraries(
        Sand_Rogue SDL2 GLEW GL assimp
)