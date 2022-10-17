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

void drawHorizontalTextureLine(CanvasPoint from, CanvasPoint to, TextureMap tm, DrawingWindow& window) {
	// std::cout << "!!New Line" << std::endl;
	std::vector<CanvasPoint> canvasLine = interpolateCanvasPointWithTexture(from, to, to.x - from.x);
	if (canvasLine.size() == 1) {
		uint32_t colourNumeric = tm.pixels[from.texturePoint.x + from.texturePoint.y * tm.width];
		window.setPixelColour(round(from.x), round(from.y), colourNumeric);
		return;
	}
	//std::cout << "Draw From: " << from << " t.x: " << from.texturePoint.x << " t.y: " << from.texturePoint.y << std::endl;
	//std::cout << "Draw To: " << to << " t.x: " << to.texturePoint.x << " t.y: " << to.texturePoint.y << std::endl;
	for (auto c: canvasLine) {
		// std::cout << "Draw: " << c << " t.x: " << c.texturePoint.x << " t.y: " << c.texturePoint.y << std::endl;
		int x = c.texturePoint.x;
		int y = c.texturePoint.y;
		uint32_t colourNumeric = tm.pixels.at(x + y * tm.width);
		//colourNumeric = (0xFF << 24) + (int(float(c.texturePoint.x) / 3.0) << 16) + (int(float(c.texturePoint.y) / 3.0) << 8);
		window.setPixelColour(round(c.x), round(c.y), colourNumeric);
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

CanvasPoint findFilledFourthPoint(CanvasPoint top, CanvasPoint mid, CanvasPoint bottom) {
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
	return CanvasPoint(xFourth, yFourth);
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
	CanvasPoint r, l, n = findFilledFourthPoint(top, mid, bottom);
	// find right and left points
	if (n.x > mid.x) {
		r = n;
		l = mid;
	}
	else {
		r = mid;
		l = n;
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

CanvasPoint findTextureFourthPoint(CanvasPoint top, CanvasPoint mid, CanvasPoint bottom) {
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
	CanvasPoint n = CanvasPoint(xFourth, yFourth);
	// calculate n point TexturePoint
	glm::vec3 fromXTexture(top.y, top.texturePoint.x, top.texturePoint.y); 
	glm::vec3 toXTexture(bottom.y, bottom.texturePoint.x, bottom.texturePoint.y);
	// fixme - number of steps can possibly not work with texture
	std::vector<CanvasPoint> fullSide = interpolateCanvasPointWithTexture(top, bottom, bottom.y - top.y);
	// fixme - the vector is *rounding* the index
	n.texturePoint.x = fullSide[mid.y - top.y].texturePoint.x;
	n.texturePoint.y = fullSide[mid.y - top.y].texturePoint.y;
	return n;
}

int drawlimit = 1;

void drawTextureTriangle(CanvasTriangle t, DrawingWindow& window, TextureMap tm) {
	CanvasPoint top = t[0];
	CanvasPoint mid = t[1];
	CanvasPoint bottom = t[2];
	std::cout << "top: " << top << " mid: " << mid << " bottom: " << bottom << std::endl;
	// divide to 2 triangles (find 4th ver)
	CanvasPoint r, l;
	CanvasPoint n = findTextureFourthPoint(top, mid, bottom);
	std::cout << "New Canvas Point: " << n << " t.x: " << n.texturePoint.x << " t.y: " << n.texturePoint.y << std::endl;
	// find right and left points
	if (n.x > mid.x) {
		r = n;
		l = mid;
	}
	else {
		r = mid;
		l = n;
	}
	std::cout << "r: " << r << ", l: " << l << std::endl;
	// color top triangle
	float topTriangleSectionHeight = r.y - top.y;
	std::vector<CanvasPoint> rightSide = interpolateCanvasPointWithTexture(top, r, topTriangleSectionHeight);
	std::vector<CanvasPoint> leftSide = interpolateCanvasPointWithTexture(top, l, topTriangleSectionHeight);
	for (int i = 0; i < topTriangleSectionHeight; i++) {
		CanvasPoint f = leftSide.at(i);
		CanvasPoint t = rightSide.at(i);
		drawHorizontalTextureLine(f, t, tm, window);
	}
	// color bottom triangle
	rightSide = interpolateCanvasPointWithTexture(r, bottom, bottom.y - r.y);
	leftSide = interpolateCanvasPointWithTexture(l, bottom, bottom.y - l.y);
	for (int i = mid.y; i < bottom.y; i++) {
		CanvasPoint f = leftSide.at(i - mid.y);
		CanvasPoint t = rightSide.at(i - mid.y);
		drawHorizontalTextureLine(f, t, tm, window);
	}
}

void drawTextureTriangleWrapper(DrawingWindow& window) {
	TextureMap tm = TextureMap("C:\\Users\\ADMIN\\Documents\\HUJI\\D Semester A\\Computer Graphics\\RedNoise\\src\\texture.ppm");
	//for (int i = 0; i < 240; i++) {
	//	CanvasPoint f = CanvasPoint(0, i);
	//	f.texturePoint = TexturePoint(0, i);
	//	CanvasPoint t = CanvasPoint(320, i);
	//	t.texturePoint = TexturePoint(240, i);
	//	drawHorizontalTextureLine(f, t, tm, window);
	//}

	CanvasPoint top = CanvasPoint(160, 10);
	top.texturePoint = TexturePoint(195, 5);
	CanvasPoint mid = CanvasPoint(10, 150);
	mid.texturePoint = TexturePoint(65, 330);
	CanvasPoint bottom = CanvasPoint(300, 230);
	bottom.texturePoint = TexturePoint(395, 380);
	CanvasTriangle t = CanvasTriangle(top, mid, bottom);
	drawTextureTriangle(t, window, tm);
	drawStrokedTriangle(t, Colour(255, 255, 255), window);
}