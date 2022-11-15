#include "Week6.h"

#define WIDTH 320
#define HEIGHT 240

RayTriangleIntersection findInteractionWithTriangle(glm::vec3 camera, glm::vec3 ray, const ModelTriangle& triangle) {
	glm::vec3 p0 = triangle.vertices[0];
	glm::vec3 p1 = triangle.vertices[1];
	glm::vec3 p2 = triangle.vertices[2];
	// class algorithem
	glm::vec3 e0 = p1 - p0;
	glm::vec3 e1 = p2 - p0;
	glm::vec3 SPVector = camera - p0;
	glm::mat3 DEMatrix(-ray, e0, e1);
	glm::vec3 possibleSolution = glm::inverse(DEMatrix) * SPVector;
	// RayTriangleIntersection fields
	glm::vec3 intersectionPoint = camera + ray * possibleSolution.x;
	// check if intersectionPoint inside triangle
	bool inU = 0 <= possibleSolution.y && possibleSolution.y <= 1;
	bool inV = 0 <= possibleSolution.z && possibleSolution.z <= 1;
	bool inUV = possibleSolution.y + possibleSolution.z <= 1;
	bool beforeCamera = possibleSolution.x > 0;
	int isIntersectionPointInsideTriangle = (inU && inV && inUV && beforeCamera) ? 1 : 0;
	// return triangle
	return RayTriangleIntersection(intersectionPoint, possibleSolution.x, triangle, isIntersectionPointInsideTriangle);
}

RayTriangleIntersection getClosestIntersection(glm::vec3 camera, glm::vec3 ray, std::vector<ModelTriangle> modelTriangles) {
	RayTriangleIntersection minDistIntersection;
	RayTriangleIntersection checkedIntersection;

	for (auto triangle : modelTriangles) {
		checkedIntersection = findInteractionWithTriangle(camera, ray, triangle);
		if (checkedIntersection.triangleIndex == 1 && checkedIntersection.distanceFromCamera < minDistIntersection.distanceFromCamera) {
			minDistIntersection = checkedIntersection;
		}
	}

	return minDistIntersection;
}

void drawRayCast(DrawingWindow& window, glm::vec3 camera) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile("");
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			// find the ray that coresponds with the point (j,i)

			// find the intersection point between ray and model
			
			// traspose intersectionPoint to ??what??

			// color the window at (j,i) with the intersection triangle color
		}
	}
}