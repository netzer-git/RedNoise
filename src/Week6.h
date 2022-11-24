#include "RayTriangleIntersection.h"
#include <glm/glm.hpp>
#include "ObjParser.h"
#include "ModelTriangle.h"
#include <DrawingWindow.h>

// for Week7
RayTriangleIntersection getClosestIntersection(glm::vec3 startPoint, glm::vec3 ray, std::vector<ModelTriangle> modelTriangles);
// for Week6
void drawRayCast(DrawingWindow& window, glm::vec3 camera);