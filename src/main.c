#include "cat_renderer.h"

#include <stdio.h>

int main(void){
    if(!initRenderer())
        return -1;

    // Init window
    GLFWwindow* window = createWindow(800, 600, "Test");
    if(!window) {
        printf("Failed to create window");
    }else{
        makeContextCurrent(window);
    }

    if(!initGlad()){
        stopRenderer();
        return -1;
    }
    setWindowResizable(window, false);
    setVsyncEnabled(window, true);

    // Loop
    while(!windowShouldClose(window)) {
        // Do stuff

        swapBuffers(window);
        pollRenderer();
    }

    stopRenderer();
    destroyWindow(window);
    return 0;
}
