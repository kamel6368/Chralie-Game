#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>
class Container : public Collider
{
private:
	int i_ammoAmount;
public:
	Container(int i_ammoAmount);
	int iGetAmmo();
};