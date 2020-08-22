//
// Created by frazor on 30/07/2020.
//

#include "Sand_Window_3D.h"



SDL_Window* Sand_Window_Create(){

    SDL_Init(
        SDL_INIT_EVENTS |
        SDL_INIT_TIMER |
        SDL_INIT_VIDEO
    );

    SDL_Window *window;

    window = SDL_CreateWindow(
        WINDOW_TITLE,                                 // window title
        100,                                       // initial x position
        250,                                       // initial y position
        WINDOW_WIDTH,                                 // width, in pixels
        WINDOW_HEIGHT,                                // height, in pixels
        SDL_WINDOW_OPENGL                        // flags
    );

    ////////////// initializing OpenGL 3.3 ///////////////

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION,
        3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION,           // set the OpenGL version
        3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    SDL_GLContext gfx;

    gfx = SDL_GL_CreateContext(                         // create our windows OpenGL context
        window
    );

    if (gfx == NULL) {

        printf(
            "OpenGL context could not be created!"
        );

        Sand_Window_Destroy(
            window
        );

        assert(
            false
        );
    }

    if (glewInit() != GLEW_OK) {                          // generate the OpenGL functions

        printf(
            "failed to initialize openGL (GLEW)."
        );

        Sand_Window_Destroy(
            window
        );

        assert(
            false
        );
    }

    SDL_GL_SetSwapInterval(
        1                                    // 1 = vsync
    );

    printf(
        "OpenGL Version : %s\n",
        glGetString(GL_VERSION)
    );

    glClearColor(                                    // the window background color
        0.05f,
        0.02f,
        0.01f,
        1.0f
    );

    glEnable(
        GL_DEPTH_TEST
    );

    glEnable(GL_BLEND);

    return window;
}

void Sand_Window_Destroy(
    SDL_Window* window){

    SDL_DestroyWindow(
        window
    );

    SDL_Quit();
}
