#include "Week4.h"

// draw
void drawRasterisedDepthByCamera(DrawingWindow& window, glm::vec3 cameraPos, glm::mat3 cameraOrMat);
// translation
void moveCameraLeft(DrawingWindow& window, glm::vec3 &cameraPos);
void moveCameraRight(DrawingWindow& window, glm::vec3 &cameraPos);
void moveCameraUp(DrawingWindow& window, glm::vec3 &cameraPos);
void moveCameraDown(DrawingWindow& window, glm::vec3 &cameraPos);
// rotation
void rotateClock(DrawingWindow& window, glm::vec3& cameraPos);
void rotateUp(DrawingWindow& window, glm::vec3& cameraPos);

// translation - centered camera
void rotateUpMat(DrawingWindow& window, glm::mat3& cameraPos);
void rotateClockMat(DrawingWindow& window, glm::mat3& cameraOrMat);
// rotation - centered camera