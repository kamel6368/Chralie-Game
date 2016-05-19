#include "Ray.h"
#include <iostream>
//private
Vector2f Ray::cEndOfRayDirUpward()
{
	Vector2f c_endOfRay = Vector2f(c_sourcePosition.x, 0);
	for (int i_i = 0; i_i < c_wallSet.c_walls.size(); i_i++)
	{
		Wall &c_wall = *c_wallSet.c_walls.at(i_i);
		float f_bottomOfWall = c_wall.getPosition().y + c_wall.getSize().y / 2;
		if (f_bottomOfWall < c_sourcePosition.y && f_bottomOfWall > c_endOfRay.y && bIsInTheHorizontalBounds(c_wall))
			c_endOfRay.y = f_bottomOfWall;
	}
	return c_endOfRay;
}
Vector2f Ray::cEndOfRayDirDownward()
{
	Vector2f c_endOfRay = Vector2f(c_sourcePosition.x,FLT_MAX);
	for (int i_i = 0; i_i < c_wallSet.c_walls.size(); i_i++)
	{
		Wall &c_wall = *c_wallSet.c_walls.at(i_i);
		float f_topOfWall = c_wall.getPosition().y - c_wall.getSize().y / 2;
		if (f_topOfWall > c_sourcePosition.y && f_topOfWall < c_endOfRay.y &&  bIsInTheHorizontalBounds(c_wall))
			c_endOfRay.y = f_topOfWall;
	}
	return c_endOfRay;
}
Vector2f Ray::cEndOfRayDirLeft()
{
	Vector2f c_endOfRay = Vector2f(0, c_sourcePosition.y);
	for (int i_i = 0; i_i < c_wallSet.c_walls.size(); i_i++)
	{
		Wall &c_wall = *c_wallSet.c_walls.at(i_i);
		float f_rightOfWall = c_wall.getPosition().x + c_wall.getSize().x / 2;
		if (f_rightOfWall < c_sourcePosition.x && f_rightOfWall > c_endOfRay.x && bIsInTheVerticalBounds(c_wall))
			c_endOfRay.x = f_rightOfWall;
	}
	return c_endOfRay;
}
Vector2f Ray::cEndOfRayDirRight()
{
	Vector2f c_endOfRay = Vector2f(FLT_MAX, c_sourcePosition.y);
	for (int i_i = 0; i_i < c_wallSet.c_walls.size(); i_i++)
	{
		Wall &c_wall = *c_wallSet.c_walls.at(i_i);
		float f_leftOfWall = c_wall.getPosition().x - c_wall.getSize().x / 2;
		if (f_leftOfWall > c_sourcePosition.x && f_leftOfWall < c_endOfRay.x && bIsInTheVerticalBounds(c_wall))
			c_endOfRay.x = f_leftOfWall;
	}
	return c_endOfRay;
}

bool Ray::bIsInTheHorizontalBounds(Collider &c_wall)
{
	bool b_result = false;
	float f_left = c_wall.getPosition().x - c_wall.getSize().x / 2;
	float f_right = c_wall.getPosition().x + c_wall.getSize().x / 2;
	if (c_sourcePosition.x >= f_left && c_sourcePosition.x <= f_right)
		b_result = true;
	return b_result;
}
bool Ray::bIsInTheVerticalBounds(Collider &c_wall)
{
	bool b_result = false;
	float f_top = c_wall.getPosition().y - c_wall.getSize().y / 2;
	float f_bottom = c_wall.getPosition().y + c_wall.getSize().y / 2;
	if (c_sourcePosition.y >= f_top && c_sourcePosition.y <= f_bottom)
		b_result = true;
	return b_result;
}

Vector2f Ray::cCalculateRay()
{
	Vector2f c_endOfRay;
	switch (i_direction)
	{
	case UPWARD: 
		c_endOfRay = cEndOfRayDirUpward();
		break;
	case DOWNWARD:
		c_endOfRay = cEndOfRayDirDownward();
		break;
	case LEFT: 
		c_endOfRay = cEndOfRayDirLeft();
		break;
	case RIGHT:
		c_endOfRay = cEndOfRayDirRight();
		break;
	}
	return c_endOfRay;
}

//public
Ray::Ray(int i_direction, const Vector2f &c_sourcePsosition, WallSet &c_wallSet) : 
	i_direction(i_direction), c_sourcePosition(c_sourcePsosition), c_wallSet(c_wallSet) {}
bool Ray::isInTheFieldOfView(Collider &c_object)
{
	bool b_result = false;
	Vector2f c_endOfRay = cCalculateRay();
	switch (i_direction)
	{
	case UPWARD:  
		if (bIsInTheHorizontalBounds(c_object) && c_object.getPosition().y >= c_endOfRay.y &&
			c_object.getPosition().y <= c_sourcePosition.y)
			b_result = true;
		break;
	case DOWNWARD: 
		if (bIsInTheHorizontalBounds(c_object) && c_object.getPosition().y <= c_endOfRay.y &&
			c_object.getPosition().y >= c_sourcePosition.y)
			b_result = true;
		break;
	case LEFT:
		if (bIsInTheVerticalBounds(c_object) && c_object.getPosition().x >= c_endOfRay.x &&
			c_object.getPosition().x <= c_sourcePosition.x)
			b_result = true;
		break;
	case RIGHT: 
		if (bIsInTheVerticalBounds(c_object) && c_object.getPosition().x <= c_endOfRay.x &&
			c_object.getPosition().x >= c_sourcePosition.x)
			b_result = true;
		break;
	}
	return b_result;
}