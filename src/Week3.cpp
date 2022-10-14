#include "CanvasPoint.h"
#include "CanvasTriangle.h"
#include <Colour.h>
#include "Week2.h"
#include <algorithm>
#include <iostream>
#include <TextureMap.h>

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

CanvasTriangle sortTriangle(CanvasTriangle t) {
	CanvasTriangle s = CanvasTriangle();

	return s;
}

void drawFilledTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window) {
	// sort top to bottom
	CanvasPoint a[] = { t.v0(), t.v1(), t.v2() };
	std::cout << "first t: " << t << std::endl;
	std::sort(a, a + 3, [] (CanvasPoint a, CanvasPoint b) {
		return a.y < b.y;
		});
	CanvasPoint top = a[0];
	CanvasPoint mid = a[1];
	CanvasPoint bottom = a[2];
	std::cout << "top: " << top << " mid: " << mid << " bottom: " << bottom << std::endl;
	// divide to 2 triangles (find 4th ver)
	int fm = mid.y - top.y;
	int l0 = std::max(bottom.x, top.x) - std::min(bottom.x, top.x);
	int l2 = bottom.y - top.y;
	float xFourth, m0 = (fm * l0) / l2;
	if (top.x > bottom.x) {
		xFourth = top.x - m0;
	}
	else {
		xFourth = top.x + m0;
	}
	float yFourth = mid.y;
	// find right and left points
	CanvasPoint r, l;
	if (xFourth > mid.x) {
		r = CanvasPoint(xFourth, yFourth);
		l = mid;
	}
	else {
		r = mid;
		l = CanvasPoint(xFourth, yFourth);
	}
	std::cout << "r: " << r << ", l: " << l << std::endl;
	// color top triangle
	std::vector<float> rightSide = interpolateSingleFloats(top.x, r.x, r.y - top.y);
	std::vector<float> leftSide = interpolateSingleFloats(top.x, l.x, l.y - top.y);
	for (int i = top.y; i < r.y; i++) {
		CanvasPoint f = CanvasPoint(leftSide.at(i - top.y), i);
		CanvasPoint t = CanvasPoint(rightSide.at(i - top.y), i);
		drawLine(f, t, colour, window);
	}
	// color bottom triangle
	rightSide = interpolateSingleFloats(r.x, bottom.x, bottom.y - r.y);
	leftSide = interpolateSingleFloats(l.x, bottom.x, bottom.y - l.y);
	for (int i = mid.y; i < bottom.y; i++) {
		CanvasPoint f = CanvasPoint(leftSide.at(i - mid.y), i);
		CanvasPoint t = CanvasPoint(rightSide.at(i - mid.y), i);
		drawLine(f, t, colour, window);
	}
}

void drawFilledTriangleWrapper(DrawingWindow& window) {
	CanvasTriangle t = generateRandomTriangle();
	drawFilledTriangle(t, generateRandomColour(), window);
	drawStrokedTriangle(t, Colour(255, 255, 255), window);
}

void drawTextureTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window, TextureMap tm) {
	// sort top to bottom
	CanvasPoint a[] = { t.v0(), t.v1(), t.v2() };
	std::cout << "first t: " << t << std::endl;
	std::sort(a, a + 3, [](CanvasPoint a, CanvasPoint b) {
		return a.y < b.y;
		});
	CanvasPoint top = a[0];
	CanvasPoint mid = a[1];
	CanvasPoint bottom = a[2];
	std::cout << "top: " << top << " mid: " << mid << " bottom: " << bottom << std::endl;
	// divide to 2 triangles (find 4th ver)
	int fm = mid.y - top.y;
	int l0 = std::max(bottom.x, top.x) - std::min(bottom.x, top.x);
	int l2 = bottom.y - top.y;
	float xFourth, m0 = (fm * l0) / l2;
	if (top.x > bottom.x) {
		xFourth = top.x - m0;
	}
	else {
		xFourth = top.x + m0;
	}
	float yFourth = mid.y;
	// find right and left points
	CanvasPoint r, l;
	if (xFourth > mid.x) {
		r = CanvasPoint(xFourth, yFourth);
		l = mid;
	}
	else {
		r = mid;
		l = CanvasPoint(xFourth, yFourth);
	}
	std::cout << "r: " << r << ", l: " << l << std::endl;
	// color top triangle
	std::vector<float> rightSide = interpolateSingleFloats(top.x, r.x, r.y - top.y);
	std::vector<float> leftSide = interpolateSingleFloats(top.x, l.x, l.y - top.y);
	for (int i = top.y; i < r.y; i++) {
		CanvasPoint f = CanvasPoint(leftSide.at(i - top.y), i);
		CanvasPoint t = CanvasPoint(rightSide.at(i - top.y), i);
		drawLine(f, t, colour, window);
	}
	// color bottom triangle
	rightSide = interpolateSingleFloats(r.x, bottom.x, bottom.y - r.y);
	leftSide = interpolateSingleFloats(l.x, bottom.x, bottom.y - l.y);
	for (int i = mid.y; i < bottom.y; i++) {
		CanvasPoint f = CanvasPoint(leftSide.at(i - mid.y), i);
		CanvasPoint t = CanvasPoint(rightSide.at(i - mid.y), i);
		drawLine(f, t, colour, window);
	}
}

void drawTextureTriangleWrapper(DrawingWindow& window) {
	TextureMap tm = TextureMap("C:\\Users\\ADMIN\\Documents\\HUJI\\D Semester A\\Computer Graphics\\RedNoise\\src\\texture.ppm");
	CanvasPoint top = CanvasPoint(160, 10);
	top.texturePoint = TexturePoint(195, 5);
	CanvasPoint mid = CanvasPoint(10, 150);
	mid.texturePoint = TexturePoint(65, 330);
	CanvasPoint bottom = CanvasPoint(300, 230);
	bottom.texturePoint = TexturePoint(395, 380);
	CanvasTriangle t = CanvasTriangle(top, mid, bottom);
	drawTextureTriangle(t, generateRandomColour(), window, tm);
	drawStrokedTriangle(t, Colour(255, 255, 255), window);
}