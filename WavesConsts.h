#pragma once
#include <SFML\Graphics.hpp>
#include "PropsConsts.h"
using namespace sf;

//wave of zombies positions
const int MAX_AMOUNT_OF_ZOMBIES_SPAWNED_AT_TIME = 4;
const int ZOMBIE_SPAWN_INTERVAL = 9000; //[ms]
const int AMOUNT_FOR_WAVE = 200;
const int NUMBER_OF_ZOMBIE_SPAWNPOINTS = 4;
//those indexes are fixed, no need to decrement
const int INDEX_OF_NEXT_CROSSING_WHEN_SPAWNED[NUMBER_OF_ZOMBIE_SPAWNPOINTS] = { 59,61,18,21 };
const std::pair<Vector2f, int> ZOMBIE_SPAWNPOINTS[NUMBER_OF_ZOMBIE_SPAWNPOINTS] =
{
	/* 1 */		std::pair<Vector2f,int>(Vector2f(1835, 327),LEFT),
	/* 2 */		std::pair<Vector2f,int>(Vector2f(1820, 641),LEFT),
	/* 3 */		std::pair<Vector2f,int>(Vector2f(422,577),UPWARD),
	/* 4 */		std::pair<Vector2f,int>(Vector2f(281,814),RIGHT)
};