#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Collider : public RectangleShape
{
public:
	Collider() {}
	bool bIsCollidingSide(Collider &c_sender);
	bool bIsCollidingCenter(Collider &c_sender);
};