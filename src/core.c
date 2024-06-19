#include "cat_renderer.h"

#include <stdio.h>

bool initRenderer(){
    if (!glfwInit()) {
        printf("(Error) Couldn't initialize GLFW context!\n");
        return false;
    }
    else {
        printf("Initialized GLFW successfully!\n");
        return true;
    }
}

void stopRenderer(){
    //unloadDefaultShaders();
    glfwTerminate();
    printf("Terminated GLFW context!\n");
}

bool initGlad(){
    printf("Initing GLAD...\n");
    return true;
}

void pollRenderer(){
    glfwPollEvents();
}
