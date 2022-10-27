#include "Week4.h"

// draw
void drawRasterisedDepthByCamera(DrawingWindow& window, glm::mat3 cameraMat);
// ckear
// translation
void moveCameraLeft(DrawingWindow& window, glm::vec3 &cameraPos);
void moveCameraRight(DrawingWindow& window, glm::vec3 &cameraPos);
void moveCameraUp(DrawingWindow& window, glm::vec3 &cameraPos);
void moveCameraDown(DrawingWindow& window, glm::vec3 &cameraPos);
// rotation
void rotateClock(DrawingWindow& window, glm::vec3& cameraPos);
void rotateUp(DrawingWindow& window, glm::vec3& cameraPos);