#pragma once

#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C" {
#endif

    // CORE
    bool initRenderer();
    void stopRenderer();
    bool initGlad();
    void pollRenderer();

    // WINDOW
    GLFWwindow* createWindow(int width, int height, const char* title);
    void destroyWindow(GLFWwindow* window);
    void makeContextCurrent(GLFWwindow* window);
    bool windowShouldClose(GLFWwindow* window);
    void swapBuffers(GLFWwindow* window);

    void setWindowTitle(GLFWwindow* window, const char* title);
    void setVsyncEnabled(GLFWwindow* window, bool set);
    void setWindowResizable(GLFWwindow* window, bool resizable);
    void setWindowSize(GLFWwindow* window, int width, int height);
    void setWindowPosition(GLFWwindow* window, int positionX, int positionY);
    void setWindowPositionCentered(GLFWwindow* window, int positionX, int positionY);
    void centerWindow(GLFWwindow* window);

    const char* getWindowTitle(GLFWwindow* window);
    int getWindowWidth(GLFWwindow* window);
    int getWindowHeight(GLFWwindow* window);
    int getWindowPositionX(GLFWwindow* window);
    int getWindowPositionY(GLFWwindow* window);

    // RENDERERS


    // SHADERS
    unsigned int createShader(const char* vertexShader, const char* fragmentShader);

    const char* loadShader(const char* filePath);

    void loadDefaultShaders();
    void unloadDefaultShaders();

    void useShaderProgram(unsigned int shaderProgram);
    void useDefaultShapeShaderProgram();
    void useDefaultTextureShaderProgram();

    unsigned int getCurrentShader();

    // UTILS
    bool fileExists(const char* filePath);
    unsigned int loadTextureAdvanced(const char* filePath, GLint wrapping, GLint filtering);
    unsigned int loadTexture(const char* filepath);
    const char* loadTextFile(const char* filePath);
    void unloadImage(unsigned int id);

    int getFPS();
    double getDeltaTime();
    double getElapsedTime();
    void updateFrameTime();


#ifdef __cplusplus
}
#endif
