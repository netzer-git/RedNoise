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
// lookAt - centered camera
void rotateClockMat(DrawingWindow& window, glm::vec3& cameraPos, glm::mat3& cameraOrMat);
void lookAtMid(glm::vec3& cameraPos, glm::mat3& cameraOrMat);