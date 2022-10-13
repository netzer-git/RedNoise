#include <vector>
#include <glm/glm.hpp>

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