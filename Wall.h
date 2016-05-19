#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Wall : public Collider
{
public:
	Wall(const Vector2f &c_position, const Vector2f &c_size);
};