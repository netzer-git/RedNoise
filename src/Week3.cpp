#include "CanvasPoint.h"
#include "CanvasTriangle.h"
#include <Colour.h>
#include "Week2.h"

#define WIDTH 320
#define HEIGHT 240

void drawLine(CanvasPoint from, CanvasPoint to, Colour colour, DrawingWindow& window) {
	float xDiff = to.x - from.x;
	float yDiff = to.y - from.y;
	float stepsNum = std::max(std::abs(xDiff), std::abs(yDiff));
	float xStepSize = xDiff / stepsNum;
	float yStepSize = yDiff / stepsNum;

	for (float i = 0; i < stepsNum; i++) {
		float x = from.x + xStepSize * i;
		float y = from.y + yStepSize * i;
		uint32_t colourNumeric = (255 << 24) + (int(colour.red) << 16) + (int(colour.green) << 8) + int(colour.blue);
		window.setPixelColour(round(x), round(y), colourNumeric);
	}
}

void drawLineWrapper(DrawingWindow& window) {
	CanvasPoint to = CanvasPoint(0, 0);
	CanvasPoint from = CanvasPoint(320, 240);
	Colour colour = Colour(254, 254, 254);
	drawLine(from, to, colour, window);
}

void drawStrokedTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window) {
	drawLine(t.v0(), t.v1(), colour, window);
	drawLine(t.v1(), t.v2(), colour, window);
	drawLine(t.v2(), t.v0(), colour, window);
}

CanvasTriangle generateRandomTriangle(int witdh=WIDTH, int height=HEIGHT) {
	CanvasPoint v0 = CanvasPoint(rand() % witdh, rand() % height);
	CanvasPoint v1 = CanvasPoint(rand() % witdh, rand() % height);
	CanvasPoint v2 = CanvasPoint(rand() % witdh, rand() % height);
	return CanvasTriangle(v0, v1, v2);
}

Colour generateRandomColour() {
	int red = rand() % 256;
	int blue = rand() % 256;
	int green = rand() % 256;
	return Colour(red, blue, green);
}

void drawStrokedTriangleWrapper(DrawingWindow& window) {
	CanvasTriangle t;
	Colour c;
	for (int i = 0; i < 3; i++) {
		drawStrokedTriangle(generateRandomTriangle(), generateRandomColour(), window);
	}
}

void drawFilledTriangleWrapper(CanvasTriangle t, Colour colour, DrawingWindow& window) {

}

void drawFilledTriangleWrapper(DrawingWindow& window) {
	drawFilledTriangleWrapper(generateRandomTriangle(), generateRandomColour(), window);
	drawStrokedTriangle(generateRandomTriangle(), Colour(255, 255, 255), window);
}