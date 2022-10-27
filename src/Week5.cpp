#include "Week5.h"

#define WIDTH 320
#define HEIGHT 240
#define OBJ_PATH "C:\\Users\\ADMIN\\Documents\\HUJI\\D Semester A\\Computer Graphics\\RedNoise\\src\\obj-src\\cornell-box.obj"

CanvasPoint getCanvasIntersectionPointByMat(glm::mat3 cameraPosition, glm::vec3 vertexPosition, float focalLength) {
	CanvasPoint canvasPoint = CanvasPoint();
	vertexPosition = cameraPosition * vertexPosition;
	canvasPoint.x = ((focalLength / vertexPosition.z) * -vertexPosition.x) * 150 + WIDTH / 2;
	canvasPoint.y = ((focalLength / vertexPosition.z) * vertexPosition.y) * 150 + HEIGHT / 2;
	canvasPoint.depth = -vertexPosition.z;
	return canvasPoint;
}

void drawRasterisedDepthByCamera(DrawingWindow& window, glm::mat3 cameraMat) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile(OBJ_PATH);
	// creating depthScheme and clearing it
	std::vector<float> depthScheme(HEIGHT * WIDTH, 0);
	Colour colour;
	for (auto mt : modelTriangles) {
		Colour colour = mt.colour;
		CanvasPoint v1 = getCanvasIntersectionPointByMat(cameraMat, mt.vertices[0], 2);
		CanvasPoint v2 = getCanvasIntersectionPointByMat(cameraMat, mt.vertices[1], 2);
		CanvasPoint v3 = getCanvasIntersectionPointByMat(cameraMat, mt.vertices[2], 2);
		CanvasTriangle t = CanvasTriangle(v1, v2, v3);
		drawFilledTriangleFromScheme(t, colour, depthScheme, window);
	}
}

void clearScreen(DrawingWindow& window) {
	uint32_t colourNumeric = (255 << 0) + (255 << 0) + (255 << 0) + 0;
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			window.setPixelColour(x, y, colourNumeric);
		}
	}
}

void moveCameraLeft(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.x += 1;
	clearScreen(window);
	std::cout << "Window Clear" << std::endl;
}

void moveCameraRight(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.x -= 1;
	clearScreen(window);
	std::cout << "Window Clear" << std::endl;
}

void moveCameraUp(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.y -= 1;
	clearScreen(window);
	std::cout << "Window Clear" << std::endl;

}

void moveCameraDown(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.y += 1;
	clearScreen(window);
	std::cout << "Window Clear" << std::endl;
}

void rotateUp(DrawingWindow& window, glm::vec3& cameraPos) {
	std::cout << "CameraPos (init):" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
	float deg = 0.2;
	glm::mat3 clockRotatMat = glm::mat3(1, 0, 0, 0, cos(deg), sin(deg), 0, -sin(deg), cos(deg));
	cameraPos = clockRotatMat * cameraPos;
	clearScreen(window);
	std::cout << "CameraPos:" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
	std::cout << "Window Clear" << std::endl;
}

void rotateClock(DrawingWindow& window, glm::vec3& cameraPos) {
	std::cout << "CameraPos (init):" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
	float deg = 0.2;
	glm::mat3 clockRotatMat = glm::mat3(cos(deg), 0, -sin(deg), 0, 1, 0, sin(deg), 0, cos(deg));
	cameraPos = clockRotatMat * cameraPos;
	clearScreen(window);
	std::cout << "CameraPos:" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
	std::cout << "Window Clear" << std::endl;
}