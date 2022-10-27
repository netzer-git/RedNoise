#include "Week2.h"

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
		steps.push_back(glm::vec3(from.x + i * stepSizeX, from.y + i * stepSizeY, from.z + i * stepSizeZ));
	}
	return steps;
}


std::vector<CanvasPoint> interpolateCanvasPointWithTexture(CanvasPoint from, CanvasPoint to, int numberOfValues) {
	std::vector<CanvasPoint> steps;
	float stepSizeX = (to.x - from.x) / (numberOfValues - 1);
	float stepSizeY = (to.y - from.y) / (numberOfValues - 1);
	float stepSizeTextureX = (to.texturePoint.x - from.texturePoint.x) / (numberOfValues - 1);
	float stepSizeTextureY = (to.texturePoint.y - from.texturePoint.y) / (numberOfValues - 1);

	for (int i = 0; i < numberOfValues; i++) {
		CanvasPoint n = CanvasPoint(from.x + i * stepSizeX, from.y + i * stepSizeY);
		n.texturePoint.x = from.texturePoint.x + i * stepSizeTextureX;
		n.texturePoint.y = from.texturePoint.y + i * stepSizeTextureY;
		steps.push_back(n);
	}
	return steps;
}

std::vector<CanvasPoint> interpolateCanvasPointWithDepth(CanvasPoint from, CanvasPoint to, int numberOfValues) {
	std::vector<CanvasPoint> steps;
	float stepSizeX = (to.x - from.x) / (numberOfValues - 1);
	float stepSizeY = (to.y - from.y) / (numberOfValues - 1);
	float stepSizeDepth = (to.depth - from.depth) / (numberOfValues - 1);

	for (int i = 0; i < numberOfValues; i++) {
		CanvasPoint n = CanvasPoint(from.x + i * stepSizeX, from.y + i * stepSizeY);
		n.depth = from.depth + i * stepSizeDepth;
		steps.push_back(n);
	}
	return steps;
}

void drawRGBColors(DrawingWindow& window, int width) {
	std::vector<glm::vec3> result;
	glm::vec3 topLeft(255, 0, 0);        // red 
	glm::vec3 topRight(0, 0, 255);       // blue 
	glm::vec3 bottomRight(0, 255, 0);    // green 
	glm::vec3 bottomLeft(255, 255, 0);   // yellow

	for (size_t y = 0; y < window.height; y++) {
		glm::vec3 from(255, y, 0);
		glm::vec3 to(0, y, 255 - y);
		result = interpolateThreeElementValues(from, to, width);
		for (size_t x = 0; x < window.width; x++) {
			float red = result[x].x;
			float green = result[x].y;
			float blue = result[x].z;
			uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
			window.setPixelColour(x, y, colour);
		}
	}
}