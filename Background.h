#pragma once
#include <SFML\Graphics.hpp>
#include "Constants.h"

using namespace sf;


class Background
{
private:
	RectangleShape c_rectangles[NUMBER_OF_BLACK_RECTANGLES];
	RectangleShape c_blue;
public:
	Background(Vector2f &c_resolution);
	void vDraw(RenderWindow &c_window);
};