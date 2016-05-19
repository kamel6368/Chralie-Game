#pragma once
#include "WallSet.h"
#include "Charlie.h"
#include "ZombieSet.h"
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

namespace Initializer
{
	Texture* pcLoadTexture(const string &s_path); //return NULL if error occurred
	WallSet* pcCreateWallSet();
	Charlie* pcCreateCharlie(WallSet &c_wallSet);
	bool vLoadSounds(vector<SoundBuffer*> &c_sounds, int i_limit, const string &s_path); //returns false if error occurred
	Font* vLoadFont(const string &s_path); //returns NULL if error occurred
	bool vLoadAllSounds(vector<SoundBuffer*> &c_noAmmoSoundBuffers, vector<SoundBuffer*> &c_killSoundBuffers,
		vector<SoundBuffer*> &c_zombieSpawnSoundBuffers); //returns false if error occurred
}