#include "cat_renderer.h"

#include <stdio.h>

int main(void){
    if(!initRenderer())
        return -1;

    // Init window
    GLFWwindow* window = createWindow(800, 600, "CATRenderer");
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

    printf("%s\n", glGetString(GL_VERSION));

    printf("Render loop initialized!\n");
    char windowTitle[100];
    // Loop
    while(!windowShouldClose(window)) {
        sprintf(windowTitle, "CATRenderer (FPS:%d)", getFPS());
        setWindowTitle(window, windowTitle);

        swapBuffers(window);
        pollRenderer();
    }
    printf("Render loop finished.\n");

    stopRenderer();
    destroyWindow(window);
    return 0;
}
