#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
//barriers
const int NUMBER_OF_BARRIERS = 4;
const bool HORIZONTAL_BARRIER = false;
const bool VERTICAL_BARRIER = true;
const int BARRIER_HEIGHT = 50;
const int BARRIER_WIDTH = 3;
const pair<Vector2f, bool> BARRIERS[NUMBER_OF_BARRIERS] =
{
	/* 1 */	pair<Vector2f,bool>(Vector2f(1813,303),VERTICAL_BARRIER),
	/* 2 */	pair<Vector2f,bool>(Vector2f(1787,617),VERTICAL_BARRIER),
	/* 3 */	pair<Vector2f,bool>(Vector2f(398,553),HORIZONTAL_BARRIER),
	/* 4 */	pair<Vector2f,bool>(Vector2f(305,790),VERTICAL_BARRIER)
};
