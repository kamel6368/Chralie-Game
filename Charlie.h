#pragma once
#include <SFML/Graphics.hpp>
#include "WallSet.h"
#include "Collider.h"
#include "Constants.h"
#include "Bullet.h"

using namespace sf;



class Charlie : public Collider
{
private:
	WallSet &c_wallSet;
	int i_facingDirection;
public:
	Charlie(WallSet &c_wallSet);
	void vMove(int i_direction);
	Bullet* pcShoot();
	void vSetFacingDirection(int i_facingDirection);
};