#pragma once
#include "Collider.h"
#include "Constants.h"
class Bullet : public Collider
{
private:
	const int i_direction;
	Clock c_clock;
public:
	Bullet(int i_flyDirection, const Vector2f &c_spawnPosition);
	void vFly();
};