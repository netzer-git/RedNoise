#include "Week6.h"

#define WIDTH 320
#define HEIGHT 240


glm::vec3 convertPointToDirectionRay(glm::vec3 camera, glm::vec2 point, float focalLength = 2, glm::mat3 cameraRotMat = glm::mat3()) {
	glm::vec3 ray;
	glm::vec3 pointCameraSpace;
	int z = 1;
	int constScale = 45;
	pointCameraSpace.x = z * (point.x - WIDTH / 2) / (constScale * focalLength);
	pointCameraSpace.y = -z * (point.y - HEIGHT / 2) / (constScale * focalLength);
	pointCameraSpace.z = 0;
	ray = pointCameraSpace - camera;
	ray = glm::normalize(ray);
	return ray;
}

RayTriangleIntersection findInteractionWithTriangle(glm::vec3 startPoint, glm::vec3 ray, const ModelTriangle& triangle) {
	glm::vec3 p0 = triangle.vertices[0];
	glm::vec3 p1 = triangle.vertices[1];
	glm::vec3 p2 = triangle.vertices[2];
	// class algorithem
	glm::vec3 e0 = p1 - p0;
	glm::vec3 e1 = p2 - p0;
	glm::vec3 SPVector = startPoint - p0;
	glm::mat3 DEMatrix(-ray, e0, e1);
	glm::vec3 possibleSolution = glm::inverse(DEMatrix) * SPVector;
	// RayTriangleIntersection fields
	glm::vec3 intersectionPoint = startPoint + ray * possibleSolution.x;
	// check if intersectionPoint inside triangle
	bool inU = 0 <= possibleSolution.y && possibleSolution.y <= 1;
	bool inV = 0 <= possibleSolution.z && possibleSolution.z <= 1;
	bool inUV = possibleSolution.y + possibleSolution.z <= 1;
	bool beforeStartPoint = possibleSolution.x > 0;
	int isIntersectionPointInsideTriangle = (inU && inV && inUV && beforeStartPoint) ? 1 : 0;
	// return triangle
	return RayTriangleIntersection(intersectionPoint, possibleSolution.x, triangle, isIntersectionPointInsideTriangle);
}

RayTriangleIntersection getClosestIntersection(glm::vec3 startPoint, glm::vec3 ray, std::vector<ModelTriangle> modelTriangles) {
	RayTriangleIntersection minDistIntersection = RayTriangleIntersection(glm::vec3(), INT_MAX, ModelTriangle(), 0);
	RayTriangleIntersection checkedIntersection;

	for (int i = 0; i < modelTriangles.size(); i++) {
		checkedIntersection = findInteractionWithTriangle(startPoint, ray, modelTriangles[i]);
		if (checkedIntersection.triangleIndex == 1 && checkedIntersection.distanceFromCamera < minDistIntersection.distanceFromCamera) {
			minDistIntersection = checkedIntersection;
			minDistIntersection.triangleIndex = i;
		}
	}

	return minDistIntersection;
}


bool isShadowrayHittingLight(glm::vec3 point, size_t trianglePointIndex, std::vector<ModelTriangle> modelTriangles) {
	glm::vec3 lightSource = glm::vec3(0.0, 0.45, 0.5);
	glm::vec3 ray = glm::normalize(point - lightSource);
	RayTriangleIntersection closestIntersection = getClosestIntersection(lightSource, ray, modelTriangles);
	return closestIntersection.triangleIndex == trianglePointIndex;
}

void drawRayCast(DrawingWindow& window, glm::vec3 camera) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile("");
	uint32_t colourNumeric, colourBlack = (255 << 24) + (int(0) << 16) + (int(0) << 8) + int(0);
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			// find the ray that coresponds with the point (i,j)
			glm::vec3 rayToPoint = convertPointToDirectionRay(camera, glm::vec2(i, j));
			// find the intersection point between ray and model
			RayTriangleIntersection intersectionPoint = getClosestIntersection(camera, rayToPoint, modelTriangles);
			// color the window at (j,i) with the intersection triangle color
			Colour currentColour = intersectionPoint.intersectedTriangle.colour;
			// try to find shadow
			if (isShadowrayHittingLight(intersectionPoint.intersectionPoint, intersectionPoint.triangleIndex, modelTriangles)) {
				colourNumeric = (255 << 24) + (int(currentColour.red) << 16) + (int(currentColour.green) << 8) + int(currentColour.blue);
			}
			else {
				colourNumeric = colourBlack;
			}
			window.setPixelColour(i, j, colourNumeric);
		}
	}
}