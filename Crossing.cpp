#include "Crossing.h"
#include "Constants.h"
#include <iostream>

Crossing::Crossing(int i_up, int i_down, int i_right, int i_left, const Vector2f &c_position)
{
	setPosition(c_position);
	setSize(Vector2f(CROSSING_SIZE, CROSSING_SIZE));
	setOrigin(Vector2f(c_position.x + CROSSING_SIZE / 2, c_position.y + CROSSING_SIZE / 2));
	c_possibleDirections.push_back(i_up);
	c_possibleDirections.push_back(i_down);
	c_possibleDirections.push_back(i_right);
	c_possibleDirections.push_back(i_left);
}
int Crossing::iGetIndexOfFollowingCrossing(int i_facingDirection) const
{
	return c_possibleDirections[i_facingDirection - 1] - 1;
}
int Crossing::iGetRandomDirection(int i_facingDirection) const
{
	int i_newDirection;
	vector<int> c_direction;
	for (int i_i = 0; i_i < c_possibleDirections.size(); i_i++)
		if (c_possibleDirections[i_i] != 0)
			c_direction.push_back(i_i+1);
	if (c_direction.size() == 1)
		i_newDirection = c_direction[0];
	else
	{
		int i_reverseDir;
		switch (i_facingDirection)
		{
		case UPWARD: i_reverseDir = DOWNWARD; break;
		case DOWNWARD: i_reverseDir = UPWARD; break;
		case LEFT: i_reverseDir = RIGHT; break;
		case RIGHT: i_reverseDir = LEFT; break;
		}
		i_newDirection = i_reverseDir;
		while (i_newDirection == i_reverseDir)
			i_newDirection = c_direction[rand() % c_direction.size()];
	}
	return i_newDirection;
}
int Crossing::iGetNextDirection(int i_current) const
{
	while (i_current < c_possibleDirections.size() && c_possibleDirections[i_current] == 0)
		i_current++;
	return i_current < c_possibleDirections.size() ? i_current + 1 : -1;
}

