#include "ContainerSet.h"
#include "Initializer.h"

ContainerSet::ContainerSet()
{
	pc_containerTex = Initializer::pcLoadTexture(CONTAINER_TEXTURE_PATH);
}
ContainerSet::~ContainerSet()
{
	delete pc_containerTex;
	for (int i_i = 0; i_i < c_containerSet.size(); i_i++)
		delete c_containerSet[i_i];
}
int ContainerSet::iCollect(Collider &c_object)
{
	bool b_collected = false;
	vector<Container*>::iterator c_it = c_containerSet.begin();
	for (; c_it != c_containerSet.end() && !b_collected; c_it++)
		if ((**c_it).bIsCollidingSide(c_object))
			b_collected = true;
	int i_result = 0;
	if (c_containerSet.size() > 0 && b_collected)
	{
		c_it--;
		i_result = (**c_it).iGetAmmo();
		delete *c_it;
		c_containerSet.erase(c_it);
	}
	return i_result;
}
void ContainerSet::vSpawnContainer()
{
	if (c_containerSet.size() < NUMBER_OF_CONTAINER_SPAWNPOINTS)
	{
		Vector2f c_newPosition;
		bool b_shuffle;
		do
		{
			b_shuffle = false;
			c_newPosition = CONTAINER_SPAWNPOINTS[rand() % NUMBER_OF_CONTAINER_SPAWNPOINTS];
			vector<Container*>::iterator c_it = c_containerSet.begin();
			for (; c_it != c_containerSet.end() && !b_shuffle; c_it++)
				if (c_newPosition == (**c_it).getPosition())
					b_shuffle = true;

		} while (b_shuffle);
		Container *pc_new = new Container(rand() % (MAX_AMMO + 1) + (MAX_AMMO - MIN_AMMO));
		(*pc_new).setPosition(c_newPosition);
		(*pc_new).setSize(Vector2f(CONTAINER_SIZE, CONTAINER_SIZE));
		(*pc_new).setOrigin(CONTAINER_SIZE / 2, CONTAINER_SIZE / 2);
		(*pc_new).setTexture(pc_containerTex);
		c_containerSet.push_back(pc_new);
	}
}
void ContainerSet::vDraw(RenderWindow &c_window)
{
	for (int i_i = 0; i_i < c_containerSet.size(); i_i++)
		c_window.draw(*c_containerSet[i_i]);
}