#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
using namespace std;
using namespace sf;
class Crossing : public RectangleShape
{
private:
	vector<int> c_possibleDirections;
public:
	Crossing(int i_up, int i_down, int i_right, int i_left, const Vector2f &c_position);
	int iGetIndexOfFollowingCrossing(int i_facingDirection) const;
	int iGetRandomDirection(int i_facingDirection) const;
	int iGetNextDirection(int i_current) const;

};