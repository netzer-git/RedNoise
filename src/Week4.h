#include <glm/glm.hpp>
#include "ObjParser.h"
#include <CanvasPoint.h>
#include <DrawingWindow.h>
#include "Week3.h"
#include <CanvasTriangle.h>

CanvasPoint getCanvasIntersectionPoint(glm::vec3 cameraPosition, glm::vec3 vertexPosition, float focalLength);
void drawPointCloud(DrawingWindow& window);
void drawWireframe(DrawingWindow& window);
void drawRasterised(DrawingWindow& window);
void drawRasterisedDepth(DrawingWindow& window);