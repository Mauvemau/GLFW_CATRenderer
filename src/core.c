#include "cat_renderer.h"

#include <stdio.h>

bool initRenderer() {
    if (!glfwInit()) {
        printf("(Error) Couldn't initialize GLFW context!\n");
        return false;
    }
    else {
        printf("Initialized GLFW successfully!\n");
    }
    return true;
}

void stopRenderer() {
    //unloadDefaultShaders();
    glfwTerminate();
    printf("Terminated GLFW context!\n");
}

bool initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return false;
    }
    else {
        printf("Initialized GLAD successfully!\n");
    }
    return true;
}

void pollRenderer() {
    updateFrameTime();
    glfwPollEvents();
}
