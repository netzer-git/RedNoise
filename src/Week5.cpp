#include "Week5.h"

#define pi 3.14159265359
#define WIDTH 320
#define HEIGHT 240
#define OBJ_PATH "C:\\Users\\ADMIN\\Documents\\HUJI\\D Semester A\\Computer Graphics\\RedNoise\\src\\obj-src\\cornell-box.obj"

bool flag = false;

CanvasPoint getCanvasIntersectionPointByMat(glm::vec3 cameraPos ,glm::mat3 cameraRotMat, glm::vec3 vertexPosition, float focalLength) {
	// std::cout << "vp:" << vertexPosition.x << "," << vertexPosition.y << "," << vertexPosition.z << std::endl;
	glm::vec3 cameraToVertex = vertexPosition - cameraPos;
	vertexPosition = cameraToVertex * cameraRotMat;
	vertexPosition.x = ((focalLength / vertexPosition.z) * -vertexPosition.x) * 150 + WIDTH / 2;
	vertexPosition.y = ((focalLength / vertexPosition.z) * vertexPosition.y) * 150 + HEIGHT / 2;
	vertexPosition.z = -vertexPosition.z;
	CanvasPoint canvasPoint = CanvasPoint(vertexPosition.x, vertexPosition.y, vertexPosition.z);
	// std::cout << "After Transform: " << canvasPoint << std::endl;
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


void moveCameraLeft(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.x -= 1;
	std::cout << "Window Clear" << std::endl;
}

void moveCameraRight(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.x += 1;
	std::cout << "Window Clear" << std::endl;
}

void moveCameraUp(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.y -= 1;
	std::cout << "Window Clear" << std::endl;

}

void moveCameraDown(DrawingWindow& window, glm::vec3 &cameraPos) {
	cameraPos.y += 1;
	std::cout << "Window Clear" << std::endl;
}

void rotateUp(DrawingWindow& window, glm::vec3& cameraPos) {
	//std::cout << "CameraPos (init):" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
	float deg = 0.01;
	glm::mat3 upRotatMat = glm::mat3(1, 0, 0, 0, cos(deg), sin(deg), 0, -sin(deg), cos(deg));
	cameraPos = upRotatMat * cameraPos;
	//std::cout << "CameraPos:" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
}

void rotateClock(DrawingWindow& window, glm::vec3& cameraPos) {
	//std::cout << "CameraPos (init):" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
	float deg = 0.01;
	glm::mat3 clockRotatMat = glm::mat3(cos(deg), 0, sin(deg), 0, 1, 0, -sin(deg), 0, cos(deg));
	cameraPos = cameraPos * clockRotatMat;
	//std::cout << "CameraPos:" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
}

void lookAtMid(glm::vec3& cameraPos, glm::mat3& cameraOrMat) {
	glm::vec3 forward = glm::normalize(cameraPos - glm::vec3(0, 0, 0));
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
	glm::vec3 up = glm::normalize(glm::cross(forward, right));

	cameraOrMat[0] = right;
	cameraOrMat[1] = up;
	cameraOrMat[2] = forward;
}

void rotateUpMat(DrawingWindow& window, glm::vec3& cameraPos, glm::mat3& cameraOrMat) {
	float deg = 0.1;
	glm::mat3 upRotatMat = glm::mat3(1, 0, 0, 0, cos(deg), sin(deg), 0, -sin(deg), cos(deg));
	cameraOrMat += upRotatMat;
	cameraPos = upRotatMat * cameraPos;
}

void rotateClockMat(DrawingWindow& window, glm::vec3& cameraPos, glm::mat3& cameraOrMat) {
	std::cout << "CameraPos (init):" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
	float deg = 0.001;
	glm::mat3 clockRotatMat = glm::mat3(cos(deg), 0, sin(deg), 0, 1, 0, -sin(deg), 0, cos(deg));
	cameraPos = clockRotatMat * cameraPos;
	lookAtMid(cameraPos, cameraOrMat);
	std::cout << "CameraPos:" << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
}