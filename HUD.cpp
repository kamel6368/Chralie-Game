#include "HUD.h"

HUD::HUD(Vector2f &c_resolution, Font &c_font)
{
	this->c_font = c_font;
	c_score.setFont(c_font);
	c_score.setString(SCORE_STRING + std::to_string(0));
	c_score.setColor(Color::Red);
	c_bullets.setFont(c_font);
	c_bullets.setString(BULLETS_STRING + std::to_string(BEGIN_NUMBER_OF_BULLETS));
	c_bullets.setColor(Color::Red);

	int i_interval = CHARACTER_SIZE / 2;
	int i_margin = c_resolution.y / MARGIN_DEVIDER;
	c_bullets.setOrigin(0, 0);
	Vector2f c_bulletsPosition = Vector2f(i_margin, c_resolution.y - i_interval - i_margin - 2*CHARACTER_SIZE);
	c_bullets.setPosition(c_bulletsPosition);
	c_bullets.setCharacterSize(CHARACTER_SIZE);
	c_score.setOrigin(0, 0);
	Vector2f c_scorePosition = Vector2f(i_margin, c_resolution.y - i_margin - CHARACTER_SIZE);
	c_score.setPosition(c_scorePosition);
	c_score.setCharacterSize(CHARACTER_SIZE);
}

void HUD::vUpdate(int i_score, int i_bullets)
{
	c_score.setString(SCORE_STRING + std::to_string(i_score));
	c_bullets.setString(BULLETS_STRING + std::to_string(i_bullets));
}

void HUD::vDraw(RenderWindow &c_window)
{
	c_window.draw(c_bullets);
	c_window.draw(c_score);
}

