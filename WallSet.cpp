#include "WallSet.h"

//private
bool WallSet::bIsCollidingHelper(Collider &c_sender, int i_collidingType, vector<Wall*> &c_set)
{
	bool b_isColliding = false;
	for (int i_i = 0; i_i < c_set.size() && !b_isColliding; i_i++)
	{
		bool b_temp = false;
		switch (i_collidingType)
		{
		case SIDE_COLLIDING: b_temp = (*c_set.at(i_i)).bIsCollidingSide(c_sender); break;
		case CENTER_COLLIDING: b_temp = (*c_set.at(i_i)).bIsCollidingCenter(c_sender); break;
		}
		b_isColliding = b_isColliding || b_temp;
	}
	return b_isColliding;
}

//public
WallSet::WallSet(int i_numberOfWalls)
{
	c_walls.reserve(i_numberOfWalls);
}
WallSet::~WallSet()
{
	for (int i_i = 0; i_i < c_walls.size(); i_i++)
		delete c_walls[i_i];
	for (int i_i = 0; i_i < c_barriers.size(); i_i++)
		delete c_barriers[i_i];
}
bool WallSet::bIsColliding(Collider &c_sender, int i_collidingType)
{
	bool b_wallColision = bIsCollidingHelper(c_sender, i_collidingType, c_walls);
	if (!b_wallColision)
		b_wallColision = bIsCollidingHelper(c_sender, i_collidingType, c_barriers);
	return b_wallColision;
}
void WallSet::vDraw(sf::RenderWindow &c_window)
{
	for (int i_i = 0; i_i < c_walls.size(); i_i++)
		c_window.draw(*c_walls.at(i_i));
	for (int i_i = 0; i_i < c_barriers.size(); i_i++)
		c_window.draw(*c_barriers.at(i_i));
}
void WallSet::vAddWall(Wall *pc_wall)
{
	c_walls.push_back(pc_wall);
}
void WallSet::vAddBarrier(Wall *pc_wall)
{
	c_barriers.push_back(pc_wall);
}