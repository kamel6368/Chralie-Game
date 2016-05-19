#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Container.h"
using namespace std;

class ContainerSet
{
private:
	vector<Container*> c_containerSet;
	Texture *pc_containerTex;
public:
	ContainerSet();
	~ContainerSet();
	int iCollect(Collider &c_object);
	void vSpawnContainer();
	void vDraw(RenderWindow &c_window);
};