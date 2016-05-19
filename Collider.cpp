#include "Collider.h"

bool Collider::bIsCollidingSide(Collider &c_sender)
{

	float f_spriteBottom = c_sender.getPosition().y + c_sender.getSize().y / 2;
	float f_spriteTop = c_sender.getPosition().y - c_sender.getSize().y / 2;
	float f_spriteRight = c_sender.getPosition().x + c_sender.getSize().x / 2;
	float f_spriteLeft = c_sender.getPosition().x - c_sender.getSize().x / 2;

	float f_bottom = getPosition().y + getSize().y / 2;
	float f_top = getPosition().y - getSize().y / 2;
	float f_right = getPosition().x + getSize().x / 2;
	float f_left = getPosition().x - getSize().x / 2;

	bool b_isColliding = false;
	if (f_spriteBottom >= f_top &&
		f_spriteTop <= f_bottom &&
		f_spriteLeft <= f_right &&
		f_spriteRight >= f_left)
		b_isColliding = true;
	return b_isColliding;
}
bool Collider::bIsCollidingCenter(Collider &c_sender)
{
	float f_bottom = getPosition().y + getSize().y / 2;
	float f_top = getPosition().y - getSize().y / 2;
	float f_right = getPosition().x + getSize().x / 2;
	float f_left = getPosition().x - getSize().x / 2;

	bool b_isColliding = false;
	if (c_sender.getPosition().y >= f_top &&
		c_sender.getPosition().y <= f_bottom &&
		c_sender.getPosition().x <= f_right &&
		c_sender.getPosition().x >= f_left)
		b_isColliding = true;
	return b_isColliding;
}