#include "Zombie.h"
#include <iostream>
//private
void Zombie::vMove()
{
	switch (i_facingDirection)
	{
	case UPWARD: move(0,-ZOMBIE_SPEED); break;
	case LEFT: move(-ZOMBIE_SPEED,0); break;
	case RIGHT: move(ZOMBIE_SPEED,0); break;
	case DOWNWARD: move(0,ZOMBIE_SPEED); break;
	}
}
bool Zombie::bIsOnTheCrossing()
{
	bool b_result = false;
	if (getPosition().y >= CROSSINGS[i_indexOfNextCrossing].getPosition().y - CROSSING_SIZE / 2 &&
		getPosition().y <= CROSSINGS[i_indexOfNextCrossing].getPosition().y + CROSSING_SIZE / 2 &&
		getPosition().x <= CROSSINGS[i_indexOfNextCrossing].getPosition().x + CROSSING_SIZE / 2 &&
		getPosition().x >= CROSSINGS[i_indexOfNextCrossing].getPosition().x - CROSSING_SIZE / 2)
		b_result = true;
	return b_result;
}
void Zombie::vTurn()
{
	switch (i_facingDirection)
	{
	case UPWARD:
		setScale(1, 1);
		setRotation(NINETY_DEGREE);
		break;
	case LEFT:
		setScale(1, 1);
		setRotation(0);
		break;
	case RIGHT:
		setScale(-1, 1);
		setRotation(0);
		break;
	case DOWNWARD:
		setScale(1, -1);
		setRotation(-NINETY_DEGREE);
		break;
	}
}
int Zombie::iLookForObjectOnCrossing(int i_index, Collider &c_object, WallSet &c_wallSet)
{
	int i_dir = 0;
	bool b_foundObject = false;
	int i_oldFacingDirection = i_facingDirection;
	while (!b_foundObject && (i_dir = CROSSINGS[i_index].iGetNextDirection(i_dir)) != -1)
	{
		i_facingDirection = i_dir;
		if (bIsInTheFieldOfView(c_object, c_wallSet))
			b_foundObject = true;
	}
	i_facingDirection = i_oldFacingDirection;
	return b_foundObject ? i_dir : -1;
}
int Zombie::iChooseCrossingForChase(Collider &c_object)
{
	int i_objectCrossing = -1;
	for (int i_i = 0; i_i < NUMBER_OF_CROSSINGS && i_objectCrossing == -1; i_i++)
		if (CROSSINGS[i_i].getPosition().y <= c_lastSeen.y + CHARLIE_SIZE_Y / 2 &&
			CROSSINGS[i_i].getPosition().y >= c_lastSeen.y - CHARLIE_SIZE_Y / 2 &&
			CROSSINGS[i_i].getPosition().x >= c_lastSeen.x - CHARLIE_SIZE_X / 2 &&
			CROSSINGS[i_i].getPosition().x <= c_lastSeen.x + CHARLIE_SIZE_X / 2)
			i_objectCrossing = i_i;
	int i_indexOfCrossingOnPath = i_indexOfNextCrossing;
	bool b_end = false;
	while (!b_end)
	{
		int i_temp = CROSSINGS[i_indexOfCrossingOnPath].iGetIndexOfFollowingCrossing(i_facingDirection);
		if (i_temp != -1)
			i_indexOfCrossingOnPath = i_temp;
		if (i_indexOfCrossingOnPath == i_objectCrossing || i_temp == -1)
			b_end = true;
	}
	return i_indexOfCrossingOnPath;
}


//public
Zombie::Zombie(int i_direction) : i_facingDirection(i_direction)
{
	b_isChasing = false;
	c_lastSeen = Vector2f(-1, -1);
	vTurn();
}
bool Zombie::bIsChasing()
{
	return b_isChasing;
}
void Zombie::vWalkAround(Collider &c_object, WallSet &c_wallSet)
{
	vMove();
	if (bIsOnTheCrossing())
	{
		int i_indexOfCurrentCrossing = i_indexOfNextCrossing;
		int i_lookFor = iLookForObjectOnCrossing(i_indexOfCurrentCrossing, c_object, c_wallSet);
		if (i_lookFor != -1)
			i_facingDirection = i_lookFor;
		else
		{
			i_facingDirection = CROSSINGS[i_indexOfCurrentCrossing].iGetRandomDirection(i_facingDirection);
			i_indexOfNextCrossing = CROSSINGS[i_indexOfCurrentCrossing].iGetIndexOfFollowingCrossing(i_facingDirection);
		}
		vTurn();
	}
}
void Zombie::vChase(Collider &c_object, WallSet &c_wallSet)
{
	b_isChasing = true;
	vMove();
	bool b_isOnCrossing = bIsOnTheCrossing();
	if (getPosition().y <= c_lastSeen.y + CHARLIE_SIZE_Y / 2 &&
		getPosition().y >= c_lastSeen.y - CHARLIE_SIZE_Y / 2 &&
		getPosition().x >= c_lastSeen.x - CHARLIE_SIZE_X / 2 &&
		getPosition().x <= c_lastSeen.x + CHARLIE_SIZE_X / 2 && b_isOnCrossing)
	{
		int i_indexOfCurrentCrossing = i_indexOfNextCrossing;
		int i_look = iLookForObjectOnCrossing(i_indexOfCurrentCrossing, c_object, c_wallSet);
		if (i_look != -1)
		{
			b_isChasing = true;
			i_facingDirection = i_look;
		}
		else
		{
			b_isChasing = false;
			i_facingDirection = CROSSINGS[i_indexOfCurrentCrossing].iGetRandomDirection(i_facingDirection);
			c_lastSeen = Vector2f(-1, -1);
		}
		i_indexOfNextCrossing = CROSSINGS[i_indexOfCurrentCrossing].iGetIndexOfFollowingCrossing(i_facingDirection);
		vTurn();
	}
	else if(b_isOnCrossing)
	{
		i_facingDirection = CROSSINGS[i_indexOfNextCrossing].iGetRandomDirection(i_facingDirection);
		i_indexOfNextCrossing = CROSSINGS[i_indexOfNextCrossing].iGetIndexOfFollowingCrossing(i_facingDirection);
		vTurn();
		b_isChasing = false;
	}

}
bool Zombie::bIsInTheFieldOfView(Collider &c_object, WallSet &c_wallSet)
{
	Ray c_ray = Ray(i_facingDirection, getPosition(), c_wallSet);
	bool c_result = c_ray.isInTheFieldOfView(c_object);
	if (c_result)
	{
		c_lastSeen = c_object.getPosition();
		i_indexOfNextCrossing = iChooseCrossingForChase(c_object);
	}
	return c_result;
}
void Zombie::vSetNextCrossing(int i_index)
{
	i_indexOfNextCrossing = i_index;
}

