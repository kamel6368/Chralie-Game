#include "BulletSet.h"

//private
void BulletSet::vRemoveBullets(vector<int> &c_indexesToRemove)
{
	for (vector<int>::iterator c_it = c_indexesToRemove.begin(); c_it != c_indexesToRemove.end(); c_it++)
	{
		list<Bullet*>::iterator c_listIter = c_listOfBullet.begin();
		int i_temp = 0;
		while (i_temp < *c_it)
		{
			i_temp++;
			c_listIter++;
		}
		delete *c_listIter;
		c_listOfBullet.erase(c_listIter);
	}
}

//public
BulletSet::BulletSet(WallSet &c_wallSet) : c_wallSet(c_wallSet)
{
	pc_bulletTexture = Initializer::pcLoadTexture(BULLET_TEXTURE_PATH);
}
BulletSet::~BulletSet()
{
	delete pc_bulletTexture;
	for (list<Bullet*>::iterator c_it = c_listOfBullet.begin(); c_it != c_listOfBullet.end(); c_it++)
		delete *c_it;
}
void BulletSet::vAddBullet(Bullet *pc_bullet)
{
	c_listOfBullet.push_front(pc_bullet);
	(*pc_bullet).setTexture(pc_bulletTexture);
}
int BulletSet::iKillPossibleZombies(ZombieSet &c_zombieSet)
{
	int i_killCount = 0;
	vector<int> c_indexesToRemove;
	int i_indexToRemove = 0;
	for (list<Bullet*>::iterator c_it = c_listOfBullet.begin(); c_it != c_listOfBullet.end(); c_it++)
		if (c_zombieSet.bKillZombie(**c_it))
		{
			i_killCount++;
			c_indexesToRemove.push_back(i_indexToRemove++);
		}
	vRemoveBullets(c_indexesToRemove);
	return i_killCount;
}

void BulletSet::vRemovePossibleBullets()
{
	vector<int> c_indexesToRemove;
	int i_index = 0;
	for (list<Bullet*>::iterator c_it = c_listOfBullet.begin(); c_it != c_listOfBullet.end(); c_it++)
	{ 
		if (c_wallSet.bIsColliding(*(*c_it),CENTER_COLLIDING))
			c_indexesToRemove.push_back(i_index);
		i_index++;
	}
	vRemoveBullets(c_indexesToRemove);
}
void BulletSet::vContinueFlight()
{
	for (list<Bullet*>::iterator c_it = c_listOfBullet.begin(); c_it != c_listOfBullet.end(); c_it++)
		(*(*c_it)).vFly();
}
void BulletSet::vDraw(RenderWindow &c_window)
{
	for (list<Bullet*>::iterator c_it = c_listOfBullet.begin(); c_it != c_listOfBullet.end(); c_it++)
		c_window.draw(*(*c_it));
}
