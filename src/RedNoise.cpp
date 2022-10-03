#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Utils.h>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

#define WIDTH 320
#define HEIGHT 240


std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues) {
	float stepSize = (to - from) / (numberOfValues - 1);
	std::vector<float> steps;
	for (int i = 0; i < numberOfValues; i++) {
		steps.push_back(from + stepSize * i);
	}
	return steps;
}

std::vector<glm::vec3> interpolateThreeElementValues(glm::vec3 from, glm::vec3 to, int numberOfValues) {
	float stepSizeX = (to.x - from.x) / (numberOfValues - 1);
	float stepSizeY = (to.y - from.y) / (numberOfValues - 1);
	float stepSizeZ = (to.z - from.z) / (numberOfValues - 1);
	std::vector<glm::vec3> steps;
	for (int i = 0; i < numberOfValues; i++) {
		steps.push_back(glm::vec3(from.x + i*stepSizeX, from.y + i * stepSizeY, from.z + i * stepSizeZ));
	}
	return steps;
}

void draw(DrawingWindow &window) {
	window.clearPixels();
	std::vector<glm::vec3> result;
	glm::vec3 topLeft(255, 0, 0);        // red 
	glm::vec3 topRight(0, 0, 255);       // blue 
	glm::vec3 bottomRight(0, 255, 0);    // green 
	glm::vec3 bottomLeft(255, 255, 0);   // yellow

	for (size_t y = 0; y < window.height; y++) {
		glm::vec3 from(255, 0 + y, 0);
		glm::vec3 to(0, 0 + y, 255 - y);
		result = interpolateThreeElementValues(from, to, WIDTH);
		for (size_t x = 0; x < window.width; x++) {
			float red = result[x].x;
			float green = result[x].y;
			float blue = result[x].z;
			uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
			window.setPixelColour(x, y, colour);
		}
	}
}

void handleEvent(SDL_Event event, DrawingWindow &window) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) std::cout << "LEFT" << std::endl;
		else if (event.key.keysym.sym == SDLK_RIGHT) std::cout << "RIGHT" << std::endl;
		else if (event.key.keysym.sym == SDLK_UP) std::cout << "UP" << std::endl;
		else if (event.key.keysym.sym == SDLK_DOWN) std::cout << "DOWN" << std::endl;
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
