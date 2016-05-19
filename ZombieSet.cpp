#include "ZombieSet.h"
#include "Initializer.h"

//private
bool ZombieSet::bIsAnyZombieColliding(Collider &c_object, int i_collidingType)
{
	bool b_result = false;
	for (int i_i = 0; i_i < c_zombieSet.size() && !b_result; i_i++)
		switch (i_collidingType)
		{
		case SIDE_COLLIDING: 
			b_result = (*c_zombieSet[i_i]).bIsCollidingSide(c_object);
			break;
		case CENTER_COLLIDING: 
			b_result = (*c_zombieSet[i_i]).bIsCollidingCenter(c_object);
			break;
		}
	return b_result;
}

//public
ZombieSet::ZombieSet()
{
	pc_zombieTex = Initializer::pcLoadTexture(ZOMBIE_TEXTURE_PATH);
}
ZombieSet::~ZombieSet()
{
	delete pc_zombieTex;
	for (int i_i = 0; i_i < c_zombieSet.size(); i_i++)
		delete c_zombieSet[i_i];
}
void ZombieSet::vReserveSpaceForNewWave(int i_numberOfZombies)
{
	c_zombieSet.reserve(i_numberOfZombies);
}
bool ZombieSet::bKillZombie(Bullet &c_bullet)
{
	vector<Zombie*>::iterator c_it = c_zombieSet.begin();
	bool b_killed = false;
	for (; c_it != c_zombieSet.end() && !b_killed; c_it++)
		if (c_bullet.bIsCollidingSide(**c_it))
			b_killed = true;
	if (b_killed)
	{
		c_it--;
		delete *c_it;
		c_zombieSet.erase(c_it);
	}
	return b_killed;
}
void ZombieSet::vControlZombies(Charlie &c_charlie, WallSet &c_wallSet)
{
	for (int i_i = 0; i_i < c_zombieSet.size(); i_i++)
	if ((*c_zombieSet[i_i]).bIsInTheFieldOfView(c_charlie, c_wallSet) || (*c_zombieSet[i_i]).bIsChasing())
		(*c_zombieSet[i_i]).vChase(c_charlie, c_wallSet);
	else
		(*c_zombieSet[i_i]).vWalkAround(c_charlie, c_wallSet);
}
void ZombieSet::vDraw(RenderWindow &c_window)
{
	for (int i_i = 0; i_i < c_zombieSet.size(); i_i++)
		c_window.draw(*c_zombieSet[i_i]);

}
void ZombieSet::vSpawnZombies(int i_amount)
{
	if (i_amount + i_spawnedZombies > AMOUNT_FOR_WAVE)
		i_amount = AMOUNT_FOR_WAVE - i_spawnedZombies;
	for (int i_i = 0; i_i < i_amount; i_i++)
	{
		int i_spawnpointIndex = rand() % NUMBER_OF_ZOMBIE_SPAWNPOINTS;
		Zombie *pc_newZombie = new Zombie(ZOMBIE_SPAWNPOINTS[i_spawnpointIndex].second);
		(*pc_newZombie).vSetNextCrossing(INDEX_OF_NEXT_CROSSING_WHEN_SPAWNED[i_spawnpointIndex]);
		(*pc_newZombie).setPosition(ZOMBIE_SPAWNPOINTS[i_spawnpointIndex].first);
		(*pc_newZombie).setSize(Vector2f(CHARLIE_SIZE_X, CHARLIE_SIZE_Y));
		(*pc_newZombie).setOrigin(CHARLIE_SIZE_X / 2, CHARLIE_SIZE_Y / 2);
		(*pc_newZombie).setTexture(pc_zombieTex);
		c_zombieSet.push_back(pc_newZombie);
		i_spawnedZombies++;
	}
}
bool ZombieSet::bIsAnyZombieCollidingSide(Collider &c_object)
{
	return bIsAnyZombieColliding(c_object, SIDE_COLLIDING);
}
bool ZombieSet::bIsAnyZombieCollidingCenter(Collider &c_object)
{
	return bIsAnyZombieColliding(c_object, CENTER_COLLIDING);
}

