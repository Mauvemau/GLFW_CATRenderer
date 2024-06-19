#include "cat_renderer.h"

GLFWwindow* createWindow(int width, int height, const char* title) {
    //glSet2DProjectionMatrix((float)width, (float)height);
    //glSetViewMatrix(0.0f, 0.0f, 0.0f);
    //glSetModelMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return glfwCreateWindow(width, height, title, NULL, NULL);
}

void destroyWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
}

void makeContextCurrent(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
}

bool windowShouldClose(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}

void swapBuffers(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void setWindowTitle(GLFWwindow* window, const char* title) {
    glfwSetWindowTitle(window, title);
}

void setVsyncEnabled(GLFWwindow* window, bool set) {
    glfwSwapInterval(set);
}

void setWindowResizable(GLFWwindow* window, bool resizable) {
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable);
}

void setWindowSize(GLFWwindow* window, int width, int height) {
    bool resizable = glfwGetWindowAttrib(window, GLFW_RESIZABLE);

    if(!resizable) {
        setWindowResizable(window, true);
    }

    glfwSetWindowSize(window, width, height);

    if(!resizable) {
        setWindowResizable(window, false);
    }
}

void setWindowPosition(GLFWwindow* window, int positionX, int positionY) {
    glfwSetWindowPos(window, positionX, positionY);

}

void setWindowPositionCentered(GLFWwindow* window, int positionX, int positionY) {
    // Get the size of the window
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    int newPositionX = positionX - width / 2;
    int newPositionY = positionY - height / 2;

    // Set the window position
    glfwSetWindowPos(window, newPositionX, newPositionY);
}

void centerWindow(GLFWwindow* window) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    if (monitor) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (mode) {
            int centerX = mode->width / 2;
            int centerY = mode->height / 2;

            setWindowPositionCentered(window, centerX, centerY);
        }
    }
}

int getWindowWidth(GLFWwindow* window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int getWindowHeight(GLFWwindow* window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}

int getWindowPositionX(GLFWwindow* window) {
    int xPos, yPos;
    glfwGetWindowPos(window, &xPos, &yPos);
    return xPos;
}

int getWindowPositionY(GLFWwindow* window) {
    int xPos, yPos;
    glfwGetWindowPos(window, &xPos, &yPos);
    return yPos;
}
