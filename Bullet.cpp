#include "Bullet.h"

Bullet::Bullet(int i_flyDirection, const Vector2f &c_spawnPosition) : i_direction(i_flyDirection) 
{
	setFillColor(Color(255, 255, 255));
	setPosition(c_spawnPosition);
	setSize(Vector2f(BULLET_SIZE_X, BULLET_SIZE_Y));
	setOrigin(Vector2f(getSize().x / 2, getSize().y / 2));
}
void Bullet::vFly()
{
	if (c_clock.getElapsedTime().asMilliseconds() > BULLET_FLY_INTERVAL)
	{
		Vector2f c_newPosition = getPosition();
		switch (i_direction)
		{
		case UPWARD: c_newPosition.y -= BULLET_SPEED; break;
		case DOWNWARD: c_newPosition.y += BULLET_SPEED; break;
		case LEFT: c_newPosition.x -= BULLET_SPEED; break;
		case RIGHT: c_newPosition.x += BULLET_SPEED; break;
		}
		setPosition(c_newPosition);
		c_clock.restart();
	}
}