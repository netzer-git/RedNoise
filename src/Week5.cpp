#include "Week5.h"

#define WIDTH 320
#define HEIGHT 240
#define OBJ_PATH "C:\\Users\\ADMIN\\Documents\\HUJI\\D Semester A\\Computer Graphics\\RedNoise\\src\\obj-src\\cornell-box.obj"

bool flag = false;

CanvasPoint getCanvasIntersectionPointByMat(glm::vec3 cameraPos ,glm::mat3 cameraRot, glm::vec3 vertexPosition, float focalLength) {
	std::cout << "vp:" << vertexPosition.x << "," << vertexPosition.y << "," << vertexPosition.z << std::endl;
	vertexPosition -= cameraPos;
	vertexPosition.x = ((focalLength / vertexPosition.z) * -vertexPosition.x) * 150 + WIDTH / 2;
	vertexPosition.y = ((focalLength / vertexPosition.z) * vertexPosition.y) * 150 + HEIGHT / 2;
	vertexPosition.z = -vertexPosition.z;
	std::cout << "After Transform: " << vertexPosition.x << "," << vertexPosition.y << "," << vertexPosition.z << std::endl;
	vertexPosition = cameraRot * vertexPosition;
	CanvasPoint canvasPoint = CanvasPoint(vertexPosition.x, vertexPosition.y, vertexPosition.z);
	std::cout << "After Transform: " << canvasPoint << std::endl;
	return canvasPoint;
}

void drawRasterisedDepthByCamera(DrawingWindow& window, glm::vec3 cameraPosition, glm::mat3 cameraOrMat) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile(OBJ_PATH);
	// creating depthScheme and clearing it
	std::vector<float> depthScheme(HEIGHT * WIDTH, 0);
	Colour colour;
	for (auto mt : modelTriangles) {
		Colour colour = mt.colour;
		CanvasPoint v1 = getCanvasIntersectionPointByMat(cameraPosition, cameraOrMat, mt.vertices[0], 2);
		CanvasPoint v2 = getCanvasIntersectionPointByMat(cameraPosition, cameraOrMat, mt.vertices[1], 2);
		CanvasPoint v3 = getCanvasIntersectionPointByMat(cameraPosition, cameraOrMat, mt.vertices[2], 2);
		// std::cout << v1 << std::endl;
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
	cameraPos.x -= 1;
	clearScreen(window);
	std::cout << "Window Clear" << std::endl;
}

void moveCameraRight(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.x += 1;
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
	glm::mat3 upRotatMat = glm::mat3(1, 0, 0, 0, cos(deg), sin(deg), 0, -sin(deg), cos(deg));
	cameraPos = upRotatMat * cameraPos;
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

void rotateUpMat(DrawingWindow& window, glm::mat3& cameraOrMat) {
	float deg = 0.1;
	glm::mat3 upRotatMat = glm::mat3(1, 0, 0, 0, cos(deg), sin(deg), 0, -sin(deg), cos(deg));
	cameraOrMat += upRotatMat;
	clearScreen(window);
	std::cout << "Window Clear" << std::endl;
}

void rotateClockMat(DrawingWindow& window, glm::mat3& cameraOrMat) {
	float deg = 0.1;
	glm::mat3 clockRotatMat = glm::mat3(cos(deg), 0, -sin(deg), 0, 1, 0, sin(deg), 0, cos(deg));
	cameraOrMat += clockRotatMat;
	clearScreen(window);
	std::cout << "Window Clear" << std::endl;
}