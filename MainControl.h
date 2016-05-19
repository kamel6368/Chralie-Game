#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "Initializer.h"
#include "Charlie.h"
#include "BulletSet.h"
#include "HUD.h"
#include "Background.h"
#include "Zombie.h"
#include "ContainerSet.h"
#include "ErrorHandler.h"
using namespace std;
using namespace sf;

namespace MainControl
{
	//menu
	const int TITLE_CHAR_SIZE = 72;
	const int CHOICE_CHAR_SIZE_MENU = 62;
	const int SMALL_INTERVAL = 40;
	const int LARGE_INTERVAL = 60;
	const int NUMBER_OF_LINES_IN_TITLE = 3;
	const string TITLE_STRING = "CHARLIE\n      VS\n ZOMBIE";
	const string PLAY_STRING = "Play";
	const string CONTROLS_STRING = "Controls";
	const string EXIT_STRING = "Exit";
	const Color COLOR_FOR_TITLE = Color(136, 0, 21);

	//controls
	const string MOVEMENT_CONTROLS_STRING = "W,A,S,D - move";
	const string SHOOT_CONTROLS_STRING = "SPACE - shoot";
	const string PAUSE_CONTROLS_STRING = "ESC - pause";
	const string COLLECT_CONTROLS_STRING = " - collect";
	const string KILL_CONTROLS_STRING = " - kill";
	const int HORIZONTAL_MARGIN = 20;
	const int HORIZONTAL_INTERVAL = 60;
	const int SPRITE_SIZE_CONTROLS = 50;
	const Color CONTROLS_BACKGROUND_COLOR = Color(10, 16, 75);

	//pause
	const int PAUSE_CHAR_SIZE = 64;
	const int CHOICE_CHAR_SIZE_PAUSE = 58;
	const int TEXT_INTERVAL = 40;
	const string PAUSE_STRING = "PAUSE";
	const string RESUME_STRING = "Resume";

	//win-lose screen
	const int ENDSCREEN_CHAR_SIZE = 64;
	const string CONGRATS_STRING = "Congratulations!!!";
	const string WIN_STRING = "You won!";
	const string LOSE_STRING = "You lost";
	const string SCORE_STRING = "Your score: ";
	const string CLICK_ENTER_STRING = "[CLICK ENTER]";
	const Color ENDSCREEN_BACKGROUND_COLOR = Color(10, 16, 75);


	//control
	const int RESUME = 1;
	const int EXIT = 2;
	const int PLAY = 3;
	const int CONTROLS = 4;
	const int MENU = 5;
	const int END_GAME = 6;
	const int ERROR_FOUND = 7;

	void vStartGame();

	namespace Hidden
	{
		void vWaitForEnterToBeReleased(RenderWindow &c_window);
		void vSetText(Text &c_text, const Font *pc_font, int i_charSize, const string s_string, const Vector2f &c_position);
		void vDrawFromVector(RenderWindow &c_window, vector<Drawable*> &c_elements);
		int iPause(RenderWindow &c_window, Font *pc_font);
		int iMenu(RenderWindow &c_window, Font *pc_font);
		int vControls(RenderWindow &c_window, Font *pc_font);
		int iGame(RenderWindow &c_window, Font *pc_font);
		void vWinLoseScreen(RenderWindow &c_window, Font *pc_font, bool b_win, int i_score);
		void vDeleteSoundBuffers(vector<SoundBuffer*> &c_buffers);
	}
}