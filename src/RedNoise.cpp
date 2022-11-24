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
#include "Week7.h"

#define WIDTH 320
#define HEIGHT 240

glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 4.0);
glm::mat3 cameraOrMat = glm::mat3(glm::vec3(1, 0, 0),
								glm::vec3(0, 1, 0),
								glm::vec3(0, 0, 1));
glm::vec3 lightSource = glm::vec3(0.0, 0.45, 0.5);
bool orbit = false;
int mode = 0;
int cycle = 0;

void printVector(std::string name, glm::vec3 vec) {
	std::cout << name << ": " << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}

void draw(DrawingWindow &window) {
	window.clearPixels();
	// window.clearPixels();
	// drawRGBColors(window, WIDTH);
	//drawTextureTriangleWrapper(window);
	//drawPointCloud(window);
	//drawRasterised(window);
	if (orbit) {
		rotateClock(window, cameraPos);
		lookAtMid(cameraPos, cameraOrMat);
	}
	if (mode == 1) {
		drawWireframe(window);
	}
	else if (mode == 2) {
		drawRasterisedDepth(window);
	}
	else if (mode == 3) {
		drawRayCast(window, cameraPos);
	}
	else if (mode == 4) {
		drawRayCastProximity(window, cameraPos, lightSource);
	}
	drawRayCastProximity(window, cameraPos, lightSource); // TODO: DELETE
	std::cout << "Draw Cycle Finished: " << cycle << std::endl;
	printVector("lightSource", lightSource);
	cycle++;
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

		else if (event.key.keysym.sym == SDLK_1) mode = 1;
		else if (event.key.keysym.sym == SDLK_2) mode = 2;
		else if (event.key.keysym.sym == SDLK_3) mode = 3;
		else if (event.key.keysym.sym == SDLK_4) mode = 4;


		else if (event.key.keysym.sym == SDLK_PAGEUP) lightSource.y -= 0.2;
		else if (event.key.keysym.sym == SDLK_PAGEDOWN) lightSource.y += 0.2;

	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		window.savePPM("output.ppm");
		window.saveBMP("output.bmp");
	}
}

void sanityCheck() {
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	SDL_Event event;
	//sanityCheck();
	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		draw(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
