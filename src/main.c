#include "cat_renderer.h"

#include <stdio.h>

float tVertexData[] = {
    -0.5f, -0.5f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, /**/ 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, /**/ 0.0f, 1.0f,
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

    const char* vertexSourceA = loadShader("solidColorV.glsl");
    const char* fragmentSourceA = loadShader("solidColorF.glsl");
    const char* vertexSourceB = loadShader("texturedV.glsl");
    const char* fragmentSourceB = loadShader("texturedF.glsl");
    unsigned int spSolidColor = createShader(vertexSourceA, fragmentSourceA);
    unsigned int spTextured = createShader(vertexSourceB, fragmentSourceB);
    useShaderProgram(spSolidColor);

    unsigned int myTexture = loadTexture("sus.png");

    size_t tVertexDataSize = sizeof(tVertexData) / sizeof(tVertexData[0]);
    size_t tIndexSize = sizeof(tIndex) / sizeof(tIndex[0]);

    RenderData tData = rglCreateRenderData(tVertexData, tVertexDataSize, tIndex, tIndexSize);

    printf("Render loop initialized!\n");
    // Loop
    while(!windowShouldClose(window)) {
        clearScreen();

        useShaderProgram(spSolidColor);
        rglDrawElements(tData, tIndexSize);

        swapBuffers(window);
        pollRenderer();
    }
    printf("Render loop finished.\n");

    unloadTexture(myTexture);
    rglDestroyRenderData(tData);
    destroyShader(spSolidColor);
    destroyShader(spTextured);
    stopRenderer();
    destroyWindow(window);
    return 0;
}
