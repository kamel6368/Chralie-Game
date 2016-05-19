#pragma once
#include "Collider.h"
#include "Charlie.h"
#include "Ray.h"
#include <SFML\Graphics.hpp>

class Zombie : public Collider
{
private:
	int i_facingDirection;
	int i_indexOfNextCrossing;
	bool b_isChasing;
	Vector2f c_lastSeen;

	void vMove();
	bool bIsOnTheCrossing();
	void vTurn();
	int iLookForObjectOnCrossing(int i_index, Collider &c_object, WallSet &c_wallSet);
	int iChooseCrossingForChase(Collider &c_object);

public:
	Zombie(int i_direction);
	bool bIsChasing();
	void vWalkAround(Collider &c_object, WallSet &c_wallSet);
	void vChase(Collider &c_object, WallSet &c_wallSet);
	bool bIsInTheFieldOfView(Collider &c_object, WallSet &c_wallSet);
	void vSetNextCrossing(int i_index);
};