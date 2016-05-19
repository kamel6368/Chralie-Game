#include "Background.h"

Background::Background(Vector2f &c_reslution)
{
	for (int i_i = 0; i_i < NUMBER_OF_BLACK_RECTANGLES; i_i++)
	{
		c_rectangles[i_i].setOrigin(0, 0);
		c_rectangles[i_i].setFillColor(Color::Black);
		c_rectangles[i_i].setPosition(BLACK_RECTANGLES_POSITION[i_i]);
		c_rectangles[i_i].setSize(BLACK_RECTANGLES_SIZE[i_i]);
	}
	c_blue.setPosition(0, 0);
	c_blue.setSize(c_reslution);
	c_blue.setFillColor(BLUE_FOR_BACKGROUND);
}

void Background::vDraw(RenderWindow &c_window)
{
	c_window.draw(c_blue);
	for (int i_i = 0; i_i < NUMBER_OF_BLACK_RECTANGLES; i_i++)
		c_window.draw(c_rectangles[i_i]);
}