#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

//directions
const int NUMBER_OF_DIRECTIONS = 4;
const int UPWARD = 1;
const int DOWNWARD = 2;
const int RIGHT = 3;
const int LEFT = 4;

//colliding types
const int SIDE_COLLIDING = 1;
const int CENTER_COLLIDING = 2;

//charlie properties
const int CHARLIE_START_POS_X = 1092;
const int CHARLIE_START_POS_Y = 435;
const int CHARLIE_SIZE_X = 30;
const int CHARLIE_SIZE_Y = 30;
const double CHARLIE_SPEED = 2;
const int NINETY_DEGREE = 90;

//zombie properties
const int ZOMBIE_SPEED = 1;
const double ZOMBIE_MOVE_INTERVAL = 5; //[ms]
 
//bullet properties
const int BULLET_SIZE_X = 30;
const int BULLET_SIZE_Y = 30;
const double BULLET_FLY_INTERVAL = 2; //[ms]
const float BULLET_SPEED = 4;

//container properties
const int MIN_AMMO = 3;
const int MAX_AMMO = 7;
const int CONTAINER_SIZE = 30;
const int CONTAINER_SPAWN_INTERVAL = 10000; //[ms]
const int NUMBER_OF_CONTAINER_SPAWNPOINTS = 13;
const Vector2f CONTAINER_SPAWNPOINTS[NUMBER_OF_CONTAINER_SPAWNPOINTS] =
{
	/* 1 */		Vector2f(423,153),
	/* 2 */		Vector2f(423,447),
	/* 3 */		Vector2f(376,911),
	/* 4 */		Vector2f(854,932),
	/* 5 */		Vector2f(695,179),
	/* 6 */		Vector2f(1111,302),
	/* 7 */		Vector2f(1246,522),
	/* 8 */		Vector2f(1382,885),
	/* 9 */		Vector2f(1316,642),
	/* 10 */	Vector2f(1380,245),
	/* 11 */	Vector2f(1600,181),
	/* 12 */	Vector2f(1708,424),
	/* 13 */	Vector2f(1711,927)
};
