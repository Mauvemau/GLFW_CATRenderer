#include "cat_renderer.h"

static double previousFrameTime;
static double currentFrameTime;

static double fpsUpdateTime;
static int frameCount;
static double fps;

int getFPS() {
	return (int)(fps);
}

double getDeltaTime() {
	return currentFrameTime - previousFrameTime;
}

double getElapsedTime() {
	return glfwGetTime();
}

void updateFrameTime() {
	previousFrameTime = currentFrameTime;
	currentFrameTime = getElapsedTime();

	// Calculating FPS
	frameCount++;
	if (currentFrameTime - fpsUpdateTime >= 1.0) {
		fps = (double)(frameCount);
		frameCount = 0;
		fpsUpdateTime = currentFrameTime;
	}
}
