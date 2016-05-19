#pragma once
#include <vector>
#include "Zombie.h"
class ZombieSet
{
private:
	vector<Zombie*> c_zombieSet;
	Texture *pc_zombieTex;
	int i_spawnedZombies;

	bool bIsAnyZombieColliding(Collider &c_object, int i_collidingType);
public:
	ZombieSet();
	~ZombieSet();
	void vReserveSpaceForNewWave(int i_numberOfZombies);
	bool bKillZombie(Bullet &c_bullet);
	void vControlZombies(Charlie &c_charlie, WallSet &c_wallSet);
	void vDraw(RenderWindow &c_window);
	void vSpawnZombies(int i_amount);
	bool bIsAnyZombieCollidingSide(Collider &c_object);
	bool bIsAnyZombieCollidingCenter(Collider &c_object);

};