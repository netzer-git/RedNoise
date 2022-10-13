#include <Colour.h>

void drawLine(CanvasPoint from, CanvasPoint to, Colour color, DrawingWindow& window);
void drawLineWrapper(DrawingWindow& window);

void drawStrokedTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window);
void drawStrokedTriangleWrapper(DrawingWindow& window);

void drawFilledTriangleWrapper(CanvasTriangle t, Colour colour, DrawingWindow& window);
void drawFilledTriangleWrapper(DrawingWindow& window);