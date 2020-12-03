/*
*Sky Fighter
*Created by Jeremy Ziprick
*Pixel-Vision-Studios
*/

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>
#include "Game.h"

int main()
{
	srand((unsigned int)time(0)); //seed random

	//frame rate
	int fps = 0;
	sf::Time time;
	sf::Clock clock;

	//init
	Game game;
	game.init();
	int gameState = 0; //menu

	bool splash = true;
	bool running = true;

	while (splash)
		splash = game.splashScreen();

	while (running)
	{
		game.currentMusic(); //game music

		switch (gameState)
		{
		case 0: //main menu
			gameState = game.mainMenu();
			break;

		case 1: //playing game
			gameState = game.checkPlayerWinLose();
			time = clock.getElapsedTime();

			
			game.update(); //update game logic
			game.updateGraphics(); //update visuals

			++fps;
			if (game.getDebug() == 1)
			{
				if (time.asSeconds() >= 1)
				{
					game.showDebug(fps);
					clock.restart();
					fps = 0;
				}
			}
			break;

		case 2: //options
			gameState = game.optionMenu();
			break;

		case 3: //quit game
			exit(0);
			break;
		};
	}
}