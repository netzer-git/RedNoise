#include <Colour.h>
#include <TextureMap.h>
#include <CanvasTriangle.h>
#include "CanvasPoint.h"
#include "CanvasTriangle.h"
#include <Colour.h>
#include "Week2.h"
#include <algorithm>
#include <iostream>
#include <TextureMap.h>

void drawLine(CanvasPoint from, CanvasPoint to, Colour color, DrawingWindow& window);
void drawLineWrapper(DrawingWindow& window);

void drawStrokedTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window);
void drawStrokedTriangleWrapper(DrawingWindow& window);

void drawFilledTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window);
void drawFilledTriangleWrapper(DrawingWindow& window);

void drawTextureTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window, TextureMap tm);
void drawTextureTriangleWrapper(DrawingWindow& window);

void drawFilledTriangleFromScheme(CanvasTriangle t, Colour colour, std::vector<float> &colourDepthScheme, DrawingWindow& window);