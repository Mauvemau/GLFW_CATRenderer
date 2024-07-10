#include "cat_renderer.h"

#include <stdio.h>

float tVertexData[] = {
    -0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f,
};
unsigned int tIndex[] = {
    0, 1, 2
};

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

    const char* vertexSource = loadShader("testV.glsl");
    const char* fragmentSource = loadShader("testF.glsl");

    unsigned int myShaderProgram = createShader(vertexSource, fragmentSource);
    useShaderProgram(myShaderProgram);

    size_t tVertexDataSize = sizeof(tVertexData) / sizeof(tVertexData[0]);
    size_t tIndexSize = sizeof(tIndex) / sizeof(tIndex[0]);

    RenderData tData = rglCreateRenderData(tVertexData, tVertexDataSize, tIndex, tIndexSize);

    printf("Render loop initialized!\n");
    // Loop
    while(!windowShouldClose(window)) {
        clearScreen();

        rglDrawElements(tData, tIndexSize);

        swapBuffers(window);
        pollRenderer();
    }
    printf("Render loop finished.\n");

    rglDestroyRenderData(tData);
    destroyShader(myShaderProgram);
    stopRenderer();
    destroyWindow(window);
    return 0;
}
