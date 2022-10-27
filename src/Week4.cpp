#include "Week4.h"

#define INITIAL_CAMERA_POSITION glm::vec3(0.0, 0.0, 4.0)
#define INITIAL_FOCAL_LENGTH 2.0
#define WIDTH 320
#define HEIGHT 240
#define OBJ_PATH "C:\\Users\\ADMIN\\Documents\\HUJI\\D Semester A\\Computer Graphics\\RedNoise\\src\\obj-src\\cornell-box.obj"

CanvasPoint getCanvasIntersectionPoint(glm::vec3 cameraPosition, glm::vec3 vertexPosition, float focalLength) {
	CanvasPoint canvasPoint = CanvasPoint();
	vertexPosition -= cameraPosition;
	canvasPoint.x = ((focalLength / vertexPosition.z) * -vertexPosition.x) * 150 + WIDTH / 2;
	canvasPoint.y = ((focalLength / vertexPosition.z) * vertexPosition.y) * 150 + HEIGHT / 2;
	canvasPoint.depth = -vertexPosition.z;
	return canvasPoint;
}

void drawPointCloud(DrawingWindow& window) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile(OBJ_PATH);
	uint32_t colourNumeric = (255 << 24) + (255 << 16) + (255 << 8) + 255;
	for (auto mt : modelTriangles) {
		for (int i = 0; i < 3; i++) {
			CanvasPoint currentPoint = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[i], 2);
			window.setPixelColour(round(currentPoint.x), round(currentPoint.y), colourNumeric);
		}
	}
}

void drawWireframe(DrawingWindow& window) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile(OBJ_PATH);
	uint32_t colourNumeric = (255 << 24) + (255 << 16) + (255 << 8) + 255;
	Colour colour = Colour(255, 255, 255);
	for (auto mt : modelTriangles) {
		Colour colour = Colour(255, 255, 255);
		CanvasPoint v1 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[0], 2);
		CanvasPoint v2 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[1], 2);
		CanvasPoint v3 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[2], 2);
		CanvasTriangle t = CanvasTriangle(v1, v2, v3);
		drawStrokedTriangle(t, colour, window);
	}
}

void drawRasterised(DrawingWindow& window) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile(OBJ_PATH);
	uint32_t colourNumeric = (255 << 24) + (255 << 16) + (255 << 8) + 255;
	Colour colour = Colour(255, 255, 255);
	for (auto mt : modelTriangles) {
		Colour colour = mt.colour;
		CanvasPoint v1 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[0], 2);
		CanvasPoint v2 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[1], 2);
		CanvasPoint v3 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[2], 2);
		CanvasTriangle t = CanvasTriangle(v1, v2, v3);
		drawFilledTriangle(t, colour, window);
	}
}	

void drawRasterisedDepth(DrawingWindow& window) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile(OBJ_PATH);
	// creating depthScheme and clearing it
	std::vector<float> depthScheme;
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		depthScheme.push_back(0);
	}
	Colour colour;
	for (auto mt : modelTriangles) {
		Colour colour = mt.colour;
		CanvasPoint v1 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[0], 2);
		CanvasPoint v2 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[1], 2);
		CanvasPoint v3 = getCanvasIntersectionPoint(glm::vec3(0.0, 0.0, 4.0), mt.vertices[2], 2);
		CanvasTriangle t = CanvasTriangle(v1, v2, v3);
		drawFilledTriangleFromScheme(t, colour, depthScheme, window);
	}
}