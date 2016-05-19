#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "WallSet.h"
using namespace sf;

class Ray 
{
private: 
	int i_direction;
	Vector2f c_sourcePosition;
	WallSet &c_wallSet;

	Vector2f cEndOfRayDirUpward();
	Vector2f cEndOfRayDirDownward();
	Vector2f cEndOfRayDirLeft();
	Vector2f cEndOfRayDirRight();
	
	bool bIsInTheHorizontalBounds(Collider &c_wall);
	bool bIsInTheVerticalBounds(Collider &c_wall);

	Vector2f cCalculateRay();

public:
	Ray(int i_direction, const Vector2f &c_sourcePosition, WallSet &c_wallSet);
	bool isInTheFieldOfView(Collider &c_object);
};