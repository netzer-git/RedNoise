#include <Colour.h>
#include <TextureMap.h>


extern int drawlimit;

void drawLine(CanvasPoint from, CanvasPoint to, Colour color, DrawingWindow& window);
void drawLineWrapper(DrawingWindow& window);

void drawStrokedTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window);
void drawStrokedTriangleWrapper(DrawingWindow& window);

void drawFilledTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window);
void drawFilledTriangleWrapper(DrawingWindow& window);

void drawTextureTriangle(CanvasTriangle t, Colour colour, DrawingWindow& window, TextureMap tm);
void drawTextureTriangleWrapper(DrawingWindow& window);