#include "MainControl.h"

void MainControl::vStartGame()
{
	RenderWindow c_window(VideoMode(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y), "Charlie", Style::Fullscreen);
	c_window.setMouseCursorVisible(false);

	int i_choice = -1;
	Font *pc_font = Initializer::vLoadFont(FONT_PATH);
	if (pc_font == NULL)
		i_choice = ERROR_FOUND;
	while (i_choice != EXIT && i_choice != ERROR_FOUND)
	{
		i_choice = Hidden::iMenu(c_window, pc_font);
		switch (i_choice)
		{
		case PLAY: i_choice = Hidden::iGame(c_window, pc_font); break;
		case CONTROLS: Hidden::vControls(c_window, pc_font); i_choice = -1;  break;
		}
	}
	delete pc_font;
	c_window.close();
}

void MainControl::Hidden::vWaitForEnterToBeReleased(RenderWindow &c_window)
{
	Event c_event;
	bool b_released = true;
	bool b_pressed = false;
	while (c_window.pollEvent(c_event) || b_released == b_pressed)
	{
		if (c_event.type == Event::KeyReleased && c_event.key.code == Keyboard::Return)
			b_released = true;
		else if (c_event.type == Event::KeyPressed && c_event.key.code == Keyboard::Return)
		{
			b_pressed = true;
			b_released = false;
		}
	}
}
void MainControl::Hidden::vSetText(Text &c_text, const Font *pc_font, int i_charSize, const string s_string, const Vector2f &c_position)
{
	c_text.setString(s_string);
	c_text.setCharacterSize(i_charSize);
	c_text.setColor(Color::White);
	c_text.setFont(*pc_font);
	FloatRect c_temp = c_text.getLocalBounds();
	c_text.setOrigin(c_temp.left + c_temp.width / 2, c_temp.top + c_temp.height / 2);
	c_text.setPosition(c_position);
}
void MainControl::Hidden::vDrawFromVector(RenderWindow &c_window, vector<Drawable*> &c_elements)
{
	c_window.clear();
	for (int i_i = 0; i_i < c_elements.size(); i_i++)
		c_window.draw(*c_elements[i_i]);
	c_window.display();
}
int MainControl::Hidden::iPause(RenderWindow &c_window, Font *pc_font)
{
	int i_result = -1;
	Image c_curState = c_window.capture();
	Sprite c_background;
	Texture c_tex;
	c_tex.loadFromImage(c_curState);
	c_background.setTexture(c_tex);
	c_background.setPosition(0, 0);

	Vector2f c_position;
	c_position.x = DEFAULT_RESOLUTION_X / 2;

	Text c_pauseText;
	float f_y = DEFAULT_RESOLUTION_Y / 2 - CHOICE_CHAR_SIZE_PAUSE / 2 - TEXT_INTERVAL - PAUSE_CHAR_SIZE / 2;
	c_position.y = f_y;
	vSetText(c_pauseText, pc_font, PAUSE_CHAR_SIZE, PAUSE_STRING, c_position);

	Text c_resumeText;
	f_y = DEFAULT_RESOLUTION_Y / 2;
	c_position.y = f_y;
	vSetText(c_resumeText, pc_font, CHOICE_CHAR_SIZE_PAUSE, RESUME_STRING, c_position);
	c_resumeText.setColor(Color::Red);


	Text c_exitText;
	f_y = DEFAULT_RESOLUTION_Y / 2 + TEXT_INTERVAL + CHOICE_CHAR_SIZE_PAUSE / 2;
	c_position.y = f_y;
	vSetText(c_exitText, pc_font, CHOICE_CHAR_SIZE_PAUSE, EXIT_STRING, c_position);

	vector<Drawable*> c_elements;
	c_elements.push_back(&c_background);
	c_elements.push_back(&c_pauseText);
	c_elements.push_back(&c_resumeText);
	c_elements.push_back(&c_exitText);
	Event c_event;
	while (c_window.pollEvent(c_event) || i_result == -1)
	{
		vDrawFromVector(c_window, c_elements);
		if (c_event.type == Event::KeyReleased && c_event.key.code == Keyboard::Return)
		{
			if (c_resumeText.getColor() == Color::Red)
				i_result = RESUME;
			else
				i_result = MENU;
		}
		else if (c_event.type == Event::KeyPressed)
			switch (c_event.key.code)
			{
			case Keyboard::Escape:
				i_result = RESUME;
				break;
			case Keyboard::W: case Keyboard::S:
				if (c_resumeText.getColor() == Color::Red)
				{
					c_resumeText.setColor(Color::White);
					c_exitText.setColor(Color::Red);
				}
				else
				{
					c_exitText.setColor(Color::White);
					c_resumeText.setColor(Color::Red);
				}
				break;
			}
	}
	return i_result;
}
int MainControl::Hidden::iMenu(RenderWindow &c_window, Font *pc_font)
{
	RectangleShape c_background;
	c_background.setFillColor(Color::Black);
	c_background.setSize(Vector2f(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y));
	c_background.setPosition(0, 0);

	Vector2f c_position;
	c_position.x = DEFAULT_RESOLUTION_X / 2;

	Text c_title;
	float f_y = DEFAULT_RESOLUTION_Y / 2 - LARGE_INTERVAL / 2 - NUMBER_OF_LINES_IN_TITLE * TITLE_CHAR_SIZE;
	c_position.y = f_y;
	vSetText(c_title, pc_font, CHOICE_CHAR_SIZE_MENU, TITLE_STRING, c_position);
	c_title.setColor(COLOR_FOR_TITLE);

	Text c_play;
	f_y = DEFAULT_RESOLUTION_Y / 2 + LARGE_INTERVAL / 2 + CHOICE_CHAR_SIZE_MENU / 2;
	c_position.y = f_y;
	vSetText(c_play, pc_font, CHOICE_CHAR_SIZE_MENU, PLAY_STRING, c_position);
	c_play.setColor(Color::Red);

	Text c_controls;
	f_y += CHOICE_CHAR_SIZE_MENU + SMALL_INTERVAL;
	c_position.y = f_y;
	vSetText(c_controls, pc_font, CHOICE_CHAR_SIZE_MENU, CONTROLS_STRING, c_position);

	Text c_exit;
	f_y += CHOICE_CHAR_SIZE_MENU + SMALL_INTERVAL;
	c_position.y = f_y;
	vSetText(c_exit, pc_font, CHOICE_CHAR_SIZE_MENU, EXIT_STRING, c_position);

	vector<Drawable*> c_elements;
	c_elements.push_back(&c_background);
	c_elements.push_back(&c_title);
	c_elements.push_back(&c_play);
	c_elements.push_back(&c_controls);
	c_elements.push_back(&c_exit);

	Event c_event;
	int i_choice = -1;
	int i_highlighted = PLAY;
	bool b_navKeyReleased = true;
	while (c_window.pollEvent(c_event) || i_choice == -1)
	{
		vDrawFromVector(c_window, c_elements);
		if (c_event.type == Event::KeyReleased && c_event.key.code == Keyboard::Return)
			i_choice = i_highlighted;
		else if (c_event.type == Event::KeyReleased && (c_event.key.code == Keyboard::Up ||
			c_event.key.code == Keyboard::W || c_event.key.code == Keyboard::Down || c_event.key.code == Keyboard::S))
			b_navKeyReleased = true;
		else if (c_event.type == Event::KeyPressed && b_navKeyReleased)
		{
			b_navKeyReleased = false;
			switch (c_event.key.code)
			{
			case Keyboard::W: case Keyboard::Up:
				if (i_highlighted == PLAY)
				{
					c_play.setColor(Color::White);
					c_exit.setColor(Color::Red);
					i_highlighted = EXIT;
				}
				else if (i_highlighted == CONTROLS)
				{
					c_controls.setColor(Color::White);
					c_play.setColor(Color::Red);
					i_highlighted = PLAY;
				}
				else if (i_highlighted == EXIT)
				{
					c_exit.setColor(Color::White);
					c_controls.setColor(Color::Red);
					i_highlighted = CONTROLS;
				}
				vDrawFromVector(c_window, c_elements);
				break;
			case Keyboard::S: case Keyboard::Down:
				if (i_highlighted == PLAY)
				{
					c_play.setColor(Color::White);
					c_controls.setColor(Color::Red);
					i_highlighted = CONTROLS;
				}
				else if (i_highlighted == CONTROLS)
				{
					c_controls.setColor(Color::White);
					c_exit.setColor(Color::Red);
					i_highlighted = EXIT;
				}
				else if (i_highlighted == EXIT)
				{
					c_exit.setColor(Color::White);
					c_play.setColor(Color::Red);
					i_highlighted = PLAY;
				}
				vDrawFromVector(c_window, c_elements);
				break;
			}
		}
	}
	return i_choice;
}
int MainControl::Hidden::vControls(RenderWindow &c_window, Font *pc_font)
{
	Text c_movement;
	float f_y = DEFAULT_RESOLUTION_Y / 2 - SMALL_INTERVAL / 2 - CHOICE_CHAR_SIZE_MENU - SMALL_INTERVAL - CHOICE_CHAR_SIZE_MENU / 2;
	Vector2f c_position = Vector2f(DEFAULT_RESOLUTION_X / 2, f_y);
	vSetText(c_movement, pc_font, CHOICE_CHAR_SIZE_MENU, MOVEMENT_CONTROLS_STRING, c_position);

	Text c_shoot;
	f_y = DEFAULT_RESOLUTION_Y / 2 - SMALL_INTERVAL / 2 - CHOICE_CHAR_SIZE_MENU / 2;
	c_position.y = f_y;
	vSetText(c_shoot, pc_font, CHOICE_CHAR_SIZE_MENU, SHOOT_CONTROLS_STRING, c_position);

	Text c_pause;
	f_y = DEFAULT_RESOLUTION_Y / 2 + SMALL_INTERVAL / 2 + CHOICE_CHAR_SIZE_MENU / 2;
	c_position.y = f_y;
	vSetText(c_pause, pc_font, CHOICE_CHAR_SIZE_MENU, PAUSE_CONTROLS_STRING, c_position);

	float f_x;
	f_y = DEFAULT_RESOLUTION_Y / 2 + SMALL_INTERVAL / 2 + CHOICE_CHAR_SIZE_MENU + LARGE_INTERVAL + CHOICE_CHAR_SIZE_MENU / 2;
	Text c_collect;
	vSetText(c_collect, pc_font, CHOICE_CHAR_SIZE_MENU, COLLECT_CONTROLS_STRING, c_position);
	f_x = DEFAULT_RESOLUTION_X / 2 - HORIZONTAL_INTERVAL / 2 - c_collect.getLocalBounds().width / 2;
	c_collect.setPosition(Vector2f(f_x, f_y));

	Text c_kill;
	vSetText(c_kill, pc_font, CHOICE_CHAR_SIZE_MENU, KILL_CONTROLS_STRING, c_position);
	f_x = DEFAULT_RESOLUTION_X / 2 + HORIZONTAL_INTERVAL / 2 + SPRITE_SIZE_CONTROLS + c_kill.getLocalBounds().width / 2 +
		c_collect.getLocalBounds().width - c_kill.getLocalBounds().width;
	c_kill.setPosition(Vector2f(f_x, f_y));

	RectangleShape c_container;
	Texture *pc_conTex = Initializer::pcLoadTexture(CONTAINER_TEXTURE_PATH);
	if (pc_conTex == NULL)
		return ERROR_FOUND;
	c_container.setTexture(pc_conTex);
	c_container.setSize(Vector2f(SPRITE_SIZE_CONTROLS, SPRITE_SIZE_CONTROLS));
	c_container.setOrigin(SPRITE_SIZE_CONTROLS / 2, SPRITE_SIZE_CONTROLS / 2);
	f_x = DEFAULT_RESOLUTION_X / 2 - HORIZONTAL_INTERVAL / 2 - c_collect.getLocalBounds().width - SPRITE_SIZE_CONTROLS / 2;
	c_container.setPosition(Vector2f(f_x, f_y));

	RectangleShape c_zombie;
	Texture *pc_zomTex = Initializer::pcLoadTexture(ZOMBIE_TEXTURE_PATH);
	if (pc_zomTex == NULL)
	{
		delete pc_conTex;
		return ERROR_FOUND;
	}
	c_zombie.setTexture(pc_zomTex);
	c_zombie.setSize(Vector2f(SPRITE_SIZE_CONTROLS, SPRITE_SIZE_CONTROLS));
	c_zombie.setOrigin(SPRITE_SIZE_CONTROLS / 2, SPRITE_SIZE_CONTROLS / 2);
	f_x = DEFAULT_RESOLUTION_X / 2 + HORIZONTAL_INTERVAL / 2 + SPRITE_SIZE_CONTROLS / 2 + c_collect.getLocalBounds().width - c_kill.getLocalBounds().width;
	c_zombie.setPosition(Vector2f(f_x, f_y));

	RectangleShape c_background;
	float f_sizeX = HORIZONTAL_MARGIN + SPRITE_SIZE_CONTROLS + c_collect.getLocalBounds().width + HORIZONTAL_INTERVAL +
		SPRITE_SIZE_CONTROLS + c_collect.getLocalBounds().width + HORIZONTAL_MARGIN;
	float f_sizeY = SMALL_INTERVAL + CHOICE_CHAR_SIZE_MENU + SMALL_INTERVAL + CHOICE_CHAR_SIZE_MENU +
		SMALL_INTERVAL + CHOICE_CHAR_SIZE_MENU + LARGE_INTERVAL + CHOICE_CHAR_SIZE_MENU +
		SMALL_INTERVAL;
	c_background.setSize(Vector2f(f_sizeX, f_sizeY));
	c_background.setOrigin(f_sizeX / 2, f_sizeY / 2);
	c_background.setPosition(DEFAULT_RESOLUTION_X / 2, DEFAULT_RESOLUTION_Y / 2);
	c_background.setFillColor(CONTROLS_BACKGROUND_COLOR);

	vector<Drawable*> c_elements;
	c_elements.push_back(&c_background);
	c_elements.push_back(&c_movement);
	c_elements.push_back(&c_shoot);
	c_elements.push_back(&c_pause);
	c_elements.push_back(&c_collect);
	c_elements.push_back(&c_kill);
	c_elements.push_back(&c_container);
	c_elements.push_back(&c_zombie);

	Event c_event;
	bool b_end = false;
	vDrawFromVector(c_window, c_elements);
	while (c_window.pollEvent(c_event) || !b_end)
	{
		if (c_event.type == Event::KeyReleased && c_event.key.code == Keyboard::Return)
			b_end = true;
	}
	delete pc_conTex;
	delete pc_zomTex;
}
int MainControl::Hidden::iGame(RenderWindow &c_window, Font *pc_font)
{
	WallSet &c_wallSet = (*Initializer::pcCreateWallSet());
	Charlie &c_charlie = (*Initializer::pcCreateCharlie(c_wallSet));
	if (&c_charlie == NULL)
		return ERROR_FOUND;
	BulletSet c_bulletSet(c_wallSet);
	ZombieSet c_zombieSet;
	ContainerSet c_containerSet;

	bool b_errorFinder = false;
	vector<SoundBuffer*> c_noAmmoSoundBuffers;
	vector<SoundBuffer*> c_killSoundBuffers;
	vector<SoundBuffer*> c_zombieSpawnSoundBuffers;
	if (!Initializer::vLoadAllSounds(c_noAmmoSoundBuffers, c_killSoundBuffers, c_zombieSpawnSoundBuffers))
	{
		delete &c_wallSet;
		delete &c_charlie;
		return ERROR_FOUND;
	}
	Sound c_noAmmoSound, c_killSound, c_zombieSpawnSound;

	Vector2f c_resolution = Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	HUD c_hud = HUD(c_resolution, *pc_font);
	Background c_background(c_resolution);
	////////////////


	Clock c_clockMove;
	Clock c_clockShoot;
	Clock c_fpsClock;
	Clock c_clockControlZombie;
	Clock c_clockSpawnZombie;
	Clock c_clockSpawnContainer;
	bool b_isPaused = false;
	int i_score = 0;
	int i_bullets = BEGIN_NUMBER_OF_BULLETS;
	bool b_isChralieDead = false;
	c_containerSet.vSpawnContainer();

	int i_control = RESUME;
	bool b_afterPause = false;
	bool b_shootStopper = false;
	while (c_window.isOpen() && !b_isChralieDead && i_control == RESUME)
	{
		//EVENT MANAGING
		Event c_event;
		while (c_window.pollEvent(c_event))
		{
			if (c_event.type == Event::KeyPressed && c_event.key.code == Keyboard::Escape)
			{
				i_control = iPause(c_window, pc_font);
				b_afterPause = true;
			}
			else if (c_event.type == Event::KeyReleased && c_event.key.code == Keyboard::Space)
				b_shootStopper = false;
			else if(c_event.type == Event::KeyReleased)
				b_afterPause = false;
			//SHOOT CONTROL
			if (c_event.type == Event::KeyPressed && c_event.key.code == Keyboard::Space && !b_afterPause && !b_shootStopper &&
				c_clockShoot.getElapsedTime().asMilliseconds() > SHOOT_INTERVAL) 
			{
				if (i_bullets == 0)
				{
					if (c_noAmmoSound.getStatus() != Sound::Status::Playing &&
						c_killSound.getStatus() != Sound::Status::Playing)
					{
						int i_index = rand() % c_noAmmoSoundBuffers.size();
						c_noAmmoSound.setBuffer(*c_noAmmoSoundBuffers[i_index]);
						c_noAmmoSound.play();
					}
				}
				else
				{
					b_shootStopper = true;
					Bullet* pc_newBullet = c_charlie.pcShoot();
					c_bulletSet.vAddBullet(pc_newBullet);
					i_bullets--;
					c_clockShoot.restart();
				}
			}
		}

		//PLAYER CONTROL
		if (c_clockMove.getElapsedTime().asMilliseconds() > MOVE_INTERVAL)
		{
			if (Keyboard::isKeyPressed(Keyboard::W))
				c_charlie.vMove(UPWARD);
			else if (Keyboard::isKeyPressed(Keyboard::S))
				c_charlie.vMove(DOWNWARD);
			else if (Keyboard::isKeyPressed(Keyboard::A))
				c_charlie.vMove(LEFT);
			else if (Keyboard::isKeyPressed(Keyboard::D))
				c_charlie.vMove(RIGHT);
			c_clockMove.restart();
		}
		

		//BULLET MANAGING
		c_bulletSet.vContinueFlight();
		c_bulletSet.vRemovePossibleBullets();
		int i_addScore = c_bulletSet.iKillPossibleZombies(c_zombieSet);
		i_score += i_addScore;
		if (i_score == MAX_SCORE)
			i_control = END_GAME;
		if (i_addScore != 0 && c_killSound.getStatus() != Sound::Status::Playing && 
			c_noAmmoSound.getStatus() != Sound::Status::Playing)
		{
			int i_index = rand() % c_killSoundBuffers.size();
			c_killSound.setBuffer(*c_killSoundBuffers[i_index]);
			c_killSound.play();
		}

		//SPAWNING AND COTROLLING ZOMBIES
		if (c_clockControlZombie.getElapsedTime().asMilliseconds() > ZOMBIE_MOVE_INTERVAL)
		{
			c_zombieSet.vControlZombies(c_charlie, c_wallSet);
			c_clockControlZombie.restart();
		}
		if (c_clockSpawnZombie.getElapsedTime().asMilliseconds() > ZOMBIE_SPAWN_INTERVAL)
		{
			if (c_zombieSpawnSound.getStatus() != Sound::Status::Playing)
			{
				int i_index = rand() % c_zombieSpawnSoundBuffers.size();
				c_zombieSpawnSound.setBuffer(*c_zombieSpawnSoundBuffers[i_index]);
				c_zombieSpawnSound.play();
			}
			c_zombieSet.vSpawnZombies(MAX_AMOUNT_OF_ZOMBIES_SPAWNED_AT_TIME);
			c_clockSpawnZombie.restart();
		}


		//SPAWNIG AND COLLECTING CONTAINERS
		if (c_clockSpawnContainer.getElapsedTime().asMilliseconds() > CONTAINER_SPAWN_INTERVAL)
		{
			c_containerSet.vSpawnContainer();
			c_clockSpawnContainer.restart();
		}
		i_bullets += c_containerSet.iCollect(c_charlie);

		//CHECK IF CHARLIE'S DEAD
		b_isChralieDead = c_zombieSet.bIsAnyZombieCollidingCenter(c_charlie);

		//DRAWING
		if (c_fpsClock.getElapsedTime().asMilliseconds() > (SECOND_AS_MILLISECONDS / FPS))
		{
			//HUD UPDATE
			c_hud.vUpdate(i_score, i_bullets);
			c_window.clear();
			c_background.vDraw(c_window);
			c_wallSet.vDraw(c_window);
			c_containerSet.vDraw(c_window);
			c_bulletSet.vDraw(c_window);
			c_window.draw(c_charlie);
			c_zombieSet.vDraw(c_window);
			c_hud.vDraw(c_window);
			c_window.display();
			c_fpsClock.restart();
		}
	}
	c_zombieSpawnSound.stop();
	c_noAmmoSound.stop();
	c_killSound.stop();
	if (i_control != MENU)
	{
		bool b_win = i_score == MAX_SCORE;
		vector<SoundBuffer*> c_endGameSoundBuffers;
		Sound c_endGameSound;
		if (b_win)
		{
			if (!Initializer::vLoadSounds(c_endGameSoundBuffers, NUMBER_OF_WIN_SOUNDS, WIN_SOUND_PATH))
				return ERROR_FOUND;
		}
		else if (!Initializer::vLoadSounds(c_endGameSoundBuffers, NUMBER_OF_LOSE_SOUNDS, LOSE_SOUND_PATH))
			return ERROR_FOUND;
		int i_index = rand() % c_endGameSoundBuffers.size();
		c_endGameSound.setBuffer(*c_endGameSoundBuffers[i_index]);
		c_endGameSound.play();
		vWinLoseScreen(c_window, pc_font, b_win, i_score);
		c_endGameSound.stop();
		vDeleteSoundBuffers(c_endGameSoundBuffers);
	}
	vDeleteSoundBuffers(c_noAmmoSoundBuffers);
	vDeleteSoundBuffers(c_killSoundBuffers);
	vDeleteSoundBuffers(c_zombieSpawnSoundBuffers);
	delete &c_charlie;
	delete &c_wallSet;
	return i_control;
}
void MainControl::Hidden::vWinLoseScreen(RenderWindow &c_window, Font *pc_font, bool b_win, int i_score)
{
	Vector2f c_position;
	c_position.x = DEFAULT_RESOLUTION_X / 2;
	Text c_first;
	c_position.y = DEFAULT_RESOLUTION_Y / 2 - ENDSCREEN_CHAR_SIZE / 2 - SMALL_INTERVAL - ENDSCREEN_CHAR_SIZE / 2;;
	string s_temp = b_win ? CONGRATS_STRING : LOSE_STRING;
	vSetText(c_first, pc_font, ENDSCREEN_CHAR_SIZE, s_temp, c_position);

	Text c_second;
	c_position.y = DEFAULT_RESOLUTION_Y / 2;
	s_temp = b_win ? WIN_STRING : SCORE_STRING + to_string(i_score);
	vSetText(c_second, pc_font, ENDSCREEN_CHAR_SIZE, s_temp, c_position);

	Text c_clickEnter;
	c_position.y = DEFAULT_RESOLUTION_Y / 2 + ENDSCREEN_CHAR_SIZE / 2 + SMALL_INTERVAL + ENDSCREEN_CHAR_SIZE / 2;
	vSetText(c_clickEnter, pc_font, ENDSCREEN_CHAR_SIZE, CLICK_ENTER_STRING, c_position);

	vector<Drawable*> c_elements;
	c_elements.push_back(&c_first);
	c_elements.push_back(&c_second);
	c_elements.push_back(&c_clickEnter);

	vDrawFromVector(c_window, c_elements);
	Event c_event;
	bool b_end = false;
	while (c_window.pollEvent(c_event) || !b_end)
		if (c_event.type == Event::KeyReleased && c_event.key.code == Keyboard::Return)
			b_end = true;
}
void MainControl::Hidden::vDeleteSoundBuffers(vector<SoundBuffer*> &c_buffers)
{
	for (int i_i = 0; i_i < c_buffers.size(); i_i++)
		delete c_buffers[i_i];
}
