#include "Container.h"

Container::Container(int i_ammoAmount)
{
	this->i_ammoAmount = i_ammoAmount;
}
int Container::iGetAmmo()
{
	return i_ammoAmount;
}