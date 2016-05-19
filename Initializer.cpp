#include "Initializer.h"
#include "ErrorHandler.h"

WallSet* Initializer::pcCreateWallSet()
{
	WallSet *pc_wallSet = new WallSet(NUMBER_OF_WALLS);
	for (int i_i = 0; i_i < NUMBER_OF_WALLS; i_i++)
		(*pc_wallSet).vAddWall(new Wall(WALLS_POSITION[i_i], WALLS_SIZE[i_i]));
	for (int i_i = 0; i_i < NUMBER_OF_BARRIERS; i_i++)
	{
		int i_height = BARRIERS[i_i].second == VERTICAL_BARRIER ? BARRIER_HEIGHT : BARRIER_WIDTH;
		int i_width = BARRIERS[i_i].second == VERTICAL_BARRIER ? BARRIER_WIDTH : BARRIER_HEIGHT;
		Wall *pc_new = new Wall(BARRIERS[i_i].first, Vector2f(i_width, i_height));
		(*pc_new).setFillColor(Color::Red);
		(*pc_wallSet).vAddBarrier(pc_new);
	}
	return pc_wallSet;
}
Charlie* Initializer::pcCreateCharlie(WallSet &c_wallSet) //returns NULL if error occurred
{
	Charlie* pc_charlie = new Charlie(c_wallSet);
	Texture* pc_tex = pcLoadTexture(CHARLIE_TEXTURE_PATH);
	if (pc_tex == NULL)
		return NULL;
	(*pc_charlie).setTexture(pc_tex);
	(*pc_charlie).setSize(Vector2f(CHARLIE_SIZE_X, CHARLIE_SIZE_Y));
	float f_posX = (*pc_charlie).getSize().x / 2 + CHARLIE_START_POS_X;
	float f_posY = (*pc_charlie).getSize().y / 2 + CHARLIE_START_POS_Y;
	(*pc_charlie).setPosition(Vector2f(f_posX, f_posY));
	float f_sizeX = (*pc_charlie).getSize().x / 2;
	float f_sizeY = (*pc_charlie).getSize().y / 2;
	(*pc_charlie).setOrigin(f_sizeX, f_sizeY);
	(*pc_charlie).vSetFacingDirection(LEFT);
	return pc_charlie;
}
Texture* Initializer::pcLoadTexture(const std::string &s_path)
{
	Texture *pc_tex = new Texture;
	if (!(*pc_tex).loadFromFile(s_path))
	{
		delete pc_tex;
		pc_tex = NULL;
		ErrorHandler::vShowFileNotFoundMessageBox(CANNOT_FIND_FILE_STRING + s_path);
	}
	return pc_tex;
}
bool Initializer::vLoadSounds(vector<SoundBuffer*> &c_sounds, int i_limit, const string &s_path) 
{
	bool b_result = true;
	for (int i_i = 0; i_i < i_limit && b_result; i_i++)
	{
		c_sounds.push_back(new SoundBuffer);
		b_result = (*c_sounds[i_i]).loadFromFile(s_path + to_string(i_i) + WAV);
		if (!b_result)
			ErrorHandler::vShowFileNotFoundMessageBox(CANNOT_FIND_FILE_STRING + s_path + to_string(i_i) + WAV);
	}
	return b_result;
}
Font* Initializer::vLoadFont(const string &s_path)
{
	Font *pc_result = new Font;
	if (!(*pc_result).loadFromFile(s_path))
	{
		delete pc_result;
		pc_result = NULL;
		ErrorHandler::vShowFileNotFoundMessageBox(CANNOT_FIND_FILE_STRING + s_path);
	}
	return pc_result;
}
bool Initializer::vLoadAllSounds(vector<SoundBuffer*> &c_noAmmoSoundBuffers, vector<SoundBuffer*> &c_killSoundBuffers,
	vector<SoundBuffer*> &c_zombieSpawnSoundBuffers)
{
	if(!Initializer::vLoadSounds(c_noAmmoSoundBuffers, NUMBER_OF_NO_AMMO_SOUND, NO_AMMO_SOUND_PATH))
	{
		ErrorHandler::vFreeSpaceFromVectors(c_noAmmoSoundBuffers);
		return false;
	}
	if(!Initializer::vLoadSounds(c_killSoundBuffers, NUMBER_OF_KILL_SOUNDS, KILL_SOUND_PATH))
	{
		ErrorHandler::vFreeSpaceFromVectors(c_noAmmoSoundBuffers, c_killSoundBuffers);
		return false;
	}
	if(!Initializer::vLoadSounds(c_zombieSpawnSoundBuffers, NUMBER_OF_ZOMBIE_SPAWN_SOUNDS, ZOMBIE_SPAWN_SOUND_PATH))
	{
		ErrorHandler::vFreeSpaceFromVectors(c_noAmmoSoundBuffers, c_killSoundBuffers, c_zombieSpawnSoundBuffers);
		return false;
	}
	return true;
}