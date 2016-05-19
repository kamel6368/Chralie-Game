#pragma once
#include <SFML\Graphics.hpp>
#include "Constants.h"
using namespace sf;

const std::string FONT_PATH = "graphics/air.ttf";
const std::string SCORE_STRING = "Score: ";
const std::string BULLETS_STRING = "Bullets: ";

const int CHARACTER_SIZE = 50;
const int MARGIN_DEVIDER = 30;

using namespace sf;

class HUD 
{
private:
	Text c_score, c_bullets;
	Font c_font;
public:
	HUD(Vector2f &c_resolution,Font &c_font);
	void vUpdate(int i_score, int i_bullets);
	void vDraw(RenderWindow &c_window);
};