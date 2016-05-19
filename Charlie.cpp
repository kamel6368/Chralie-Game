#include "Charlie.h"

Charlie::Charlie(WallSet &c_wallSet) : c_wallSet(c_wallSet){}

void Charlie::vMove(int i_direction)
{
	Vector2f c_newPosition = getPosition();
	Vector2f c_curPosition = getPosition();
	switch (i_direction)
	{
	case UPWARD: 
		c_newPosition.y -= CHARLIE_SPEED; 
		setScale(1, 1);
		setRotation(NINETY_DEGREE); 
		break;
	case LEFT: 
		c_newPosition.x -= CHARLIE_SPEED; 
		setScale(1, 1);
		setRotation(0); 
		break;
	case RIGHT: 
		c_newPosition.x += CHARLIE_SPEED; 
		setScale(-1, 1);
		setRotation(0); 
		break;
	case DOWNWARD: 
		c_newPosition.y += CHARLIE_SPEED; 
		setScale(1, -1);
		setRotation(-NINETY_DEGREE); 
		break;
	}
	setPosition(c_newPosition);
	if (c_wallSet.bIsColliding(*this,SIDE_COLLIDING))
		setPosition(c_curPosition);
	i_facingDirection = i_direction;
}
Bullet* Charlie::pcShoot()
{
	Bullet *pc_newBullet = new Bullet(i_facingDirection,getPosition());
	return pc_newBullet;
}
void Charlie::vSetFacingDirection(int i_facingDirection)
{
	this->i_facingDirection = i_facingDirection;
}





