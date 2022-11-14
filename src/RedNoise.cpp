#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Utils.h>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include "Week2.h"
#include "Week3.h"
#include "Week4.h"
#include "Week5.h"
#include "Week6.h"

#define WIDTH 320
#define HEIGHT 240

glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 4.0);
glm::mat3 cameraOrMat = glm::mat3(glm::vec3(1, 0, 0),
								glm::vec3(0, 1, 0),
								glm::vec3(0, 0, 1));
bool orbit = false;

void draw(DrawingWindow &window) {
	window.clearPixels();
	// window.clearPixels();
	// drawRGBColors(window, WIDTH);
	//drawTextureTriangleWrapper(window);
	//drawPointCloud(window);
	//drawWireframe(window);
	//drawRasterised(window);
	//drawRasterisedDepth(window);
	if (orbit) {
		rotateClock(window, cameraPos);
		lookAtMid(cameraPos, cameraOrMat);
	}
	drawRasterisedDepthByCamera(window, cameraPos, cameraOrMat);
}

void handleEvent(SDL_Event event, DrawingWindow &window) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) std::cout << "LEFT" << std::endl;
		else if (event.key.keysym.sym == SDLK_RIGHT) std::cout << "RIGHT" << std::endl;
		else if (event.key.keysym.sym == SDLK_UP) std::cout << "UP" << std::endl;
		else if (event.key.keysym.sym == SDLK_DOWN) std::cout << "DOWN" << std::endl;
		else if (event.key.keysym.sym == SDLK_u) drawStrokedTriangleWrapper(window);
		else if (event.key.keysym.sym == SDLK_f) drawFilledTriangleWrapper(window);
		else if (event.key.keysym.sym == SDLK_t) drawTextureTriangleWrapper(window);
		else if (event.key.keysym.sym == SDLK_r) drawRasterisedDepth(window);
		else if (event.key.keysym.sym == SDLK_d) moveCameraRight(window, cameraPos);
		else if (event.key.keysym.sym == SDLK_a) moveCameraLeft(window, cameraPos);
		else if (event.key.keysym.sym == SDLK_w) moveCameraUp(window, cameraPos);
		else if (event.key.keysym.sym == SDLK_s) moveCameraDown(window, cameraPos);
		else if (event.key.keysym.sym == SDLK_e) rotateUp(window, cameraPos);

		else if (event.key.keysym.sym == SDLK_q) rotateClockMat(window, cameraPos, cameraOrMat);

		else if (event.key.keysym.sym == SDLK_o) orbit = orbit ? false : true;
	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		window.savePPM("output.ppm");
		window.saveBMP("output.bmp");
	}
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	SDL_Event event;
	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		draw(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
