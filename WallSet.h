#pragma once
#include "Wall.h"
#include "Constants.h"
#include <vector>
using namespace std;

class WallSet
{
private:
	vector<Wall*> c_walls;
	vector<Wall*> c_barriers;

	bool bIsCollidingHelper(Collider &c_sender, int i_collidingType, vector<Wall*> &c_set);
public:
	WallSet(int i_numberOfWalls);
	~WallSet();
	bool bIsColliding(Collider &c_sender, int i_collidingType);
	void vDraw(sf::RenderWindow &c_window);
	void vAddWall(Wall *pc_wall);
	void vAddBarrier(Wall *pc_wall);
	friend class Ray;
};