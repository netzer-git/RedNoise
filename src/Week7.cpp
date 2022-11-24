#include "Week7.h"
# define PI 3.14159265358979323846

float getShadowStrengthByDist(float dist) {
	float r = 1;
	return dist * (1 / 4 * PI * r * r);
}

glm::vec3 convertPointToRay(glm::vec3 camera, glm::vec2 point, float focalLength = 2, glm::mat3 cameraRotMat = glm::mat3()) {
	glm::vec3 ray;
	glm::vec3 pointCameraSpace;
	int z = 1;
	int constScale = 45;
	pointCameraSpace.x = z * (point.x - WIDTH / 2) / (constScale * focalLength);
	pointCameraSpace.y = -z * (point.y - HEIGHT / 2) / (constScale * focalLength);
	pointCameraSpace.z = 0;
	ray = pointCameraSpace - camera;
	return ray;
}

void drawRayCastProximity(DrawingWindow& window, glm::vec3 camera) {
	std::vector<ModelTriangle> modelTriangles = parseObjFile("");
	uint32_t colourNumeric;
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			// find the ray that coresponds with the point (i,j)
			glm::vec3 ray = convertPointToRay(camera, glm::vec2(i, j));
			glm::vec3 rayDirection = glm::normalize(ray);
			// find the intersection point between ray and model
			RayTriangleIntersection intersectionPoint = getClosestIntersection(camera, rayDirection, modelTriangles);
			// color the window at (j,i) with the intersection triangle color
			Colour currentColour = intersectionPoint.intersectedTriangle.colour;
			// try to find shadow
			if (isShadowrayHittingLight(intersectionPoint.intersectionPoint, intersectionPoint.triangleIndex, modelTriangles)) {
				colourNumeric = (255 << 24) + (int(currentColour.red * multiplier) << 16) + (int(currentColour.green * multiplier) << 8) + int(currentColour.blue * multiplier);
			}
			else {
				float multiplier = getShadowStrengthByDist(glm::length(ray));
				colourNumeric = (255 << 24) + (int(currentColour.red * multiplier) << 16) + (int(currentColour.green * multiplier) << 8) + int(currentColour.blue * multiplier);

			}
			window.setPixelColour(i, j, colourNumeric);
		}
	}
}