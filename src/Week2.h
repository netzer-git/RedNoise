#include <vector>
#include <glm/glm.hpp>
#include <DrawingWindow.h>
#include <CanvasPoint.h>

std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues);
std::vector<glm::vec3> interpolateThreeElementValues(glm::vec3 from, glm::vec3 to, int numberOfValues);
std::vector<CanvasPoint> interpolateCanvasPointWithTexture(CanvasPoint from, CanvasPoint to, int numberOfValues);
void drawRGBColors(DrawingWindow& window, int width);

std::vector<CanvasPoint> interpolateCanvasPointWithDepth(CanvasPoint from, CanvasPoint to, int numberOfValues);