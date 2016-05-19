#include "Wall.h"

Wall::Wall(const Vector2f &c_position, const Vector2f &c_size)
{
	Vector2f c_newPosition(c_position.x + c_size.x / 2, c_position.y + c_size.y / 2);
	setPosition(c_newPosition);
	setSize(c_size);
	setOrigin(c_size.x / 2, c_size.y / 2);
	setFillColor(Color(0, 0, 0));
}

