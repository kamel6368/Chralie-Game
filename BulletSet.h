#pragma once
#include <list>//linked list
#include <vector>
#include "Bullet.h"
#include "WallSet.h"
#include "Initializer.h"
#include "ZombieSet.h"
using namespace std;
class BulletSet
{
private:
	list<Bullet*> c_listOfBullet;
	WallSet &c_wallSet;
	Texture *pc_bulletTexture;

	void vRemoveBullets(vector<int> &c_indexesToRemove);
public:
	BulletSet(WallSet &c_wallSet);
	~BulletSet();
	void vAddBullet(Bullet *pc_bullet);
	int iKillPossibleZombies(ZombieSet &c_zombieSet);
	void vRemovePossibleBullets();
	void vContinueFlight();
	void vDraw(RenderWindow &c_window);
};