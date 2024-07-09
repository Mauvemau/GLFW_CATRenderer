#include "cat_renderer.h"

#include <stdio.h>

float tVertexData[] = {
    -0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f
};
unsigned int tVertexDataSize = 18;
unsigned int tIndex[] = {
    0, 1, 2
};
unsigned int tIndexSize = 3;

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

    RenderData tData = rglCreateRenderData(tVertexData, tVertexDataSize, tIndex, tIndexSize);

    printf("Render loop initialized!\n");
    char windowTitle[100];
    // Loop
    while(!windowShouldClose(window)) {
        clearScreen();

        /*
        glBegin(GL_TRIANGLES);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.0f, 0.5f);
            glVertex2f(0.5f, -0.5f);
        glEnd();
        */

        rglDrawElements(tData, tIndexSize / sizeof(tIndex[0]));

        swapBuffers(window);
        pollRenderer();
    }
    printf("Render loop finished.\n");

    rglDestroyRenderData(tData);

    stopRenderer();
    destroyWindow(window);
    return 0;
}
