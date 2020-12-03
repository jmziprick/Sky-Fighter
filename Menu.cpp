#include "Menu.h"

int Menu::easyHard = 0;
int Menu::numPlayers = 1;

Menu::Menu()
{
	selected = start;
	gameState = menu;

	debugOffOn = 0;
}

void Menu::render(sf::RenderWindow& window, sf::Sprite& backgroundS, sf::Sprite& menuTextS, sf::Sprite& optionTextS, sf::Font& font)
{
	backgroundS.setScale(1.1f, 1.25f);
	backgroundS.setPosition(-390, -500);
	window.draw(backgroundS);

	switch (gameState)
	{
	case menu:
		//start
		if (selected == start)
			menuTextS.setColor(sf::Color(255, 50, 50));

		menuTextS.setPosition(60, -100);
		menuTextS.setTextureRect(sf::IntRect(0, 0, 548, 176));
		window.draw(menuTextS);
		menuTextS.setColor(sf::Color(255, 255, 255)); //set back to default

		//options
		if (selected == options)
			menuTextS.setColor(sf::Color(150, 0, 0));

		menuTextS.setPosition(60, 0);
		menuTextS.setTextureRect(sf::IntRect(0, 176, 548, 176));
		window.draw(menuTextS);
		menuTextS.setColor(sf::Color(255, 255, 255)); //set back to default

		//quit
		if (selected == quit)
			menuTextS.setColor(sf::Color(150, 0, 0));

		menuTextS.setPosition(60, 100);
		menuTextS.setTextureRect(sf::IntRect(0, 550, 548, 176));
		window.draw(menuTextS);
		menuTextS.setColor(sf::Color(255, 255, 255)); //set back to default
		break;

	case options:
		//Players
		if (selected == players)
			optionTextS.setColor(sf::Color(100, 100, 50));
		optionTextS.setPosition(60, -200);
		optionTextS.setTextureRect(sf::IntRect(10, 12, 388, 40));
		window.draw(optionTextS);
		optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default
		{
			//1 player
			if (numPlayers == 1)
				optionTextS.setColor(sf::Color(255, 50, 50));
			optionTextS.setPosition(120, -140);
			optionTextS.setTextureRect(sf::IntRect(20, 72, 49, 40));
			window.draw(optionTextS);
			optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default

			//2 player
			if (numPlayers == 2)
				optionTextS.setColor(sf::Color(255, 50, 50));
			optionTextS.setPosition(200, -140);
			optionTextS.setTextureRect(sf::IntRect(124, 72, 49, 40));
			window.draw(optionTextS);
			optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default

			//3 player
			if (numPlayers == 3)
				optionTextS.setColor(sf::Color(255, 50, 50));
			optionTextS.setPosition(280, -140);
			optionTextS.setTextureRect(sf::IntRect(247, 72, 49, 40));
			window.draw(optionTextS);
			optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default
		}

		//Difficulty
		if (selected == difficulty)
			optionTextS.setColor(sf::Color(100, 100, 50));
		optionTextS.setPosition(60, 0);
		optionTextS.setTextureRect(sf::IntRect(10, 192, 438, 40));
		window.draw(optionTextS);
		optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default
		{
			if (easyHard == 0) //easy
				optionTextS.setColor(sf::Color(255, 50, 50));
			optionTextS.setPosition(120, 60);
			optionTextS.setTextureRect(sf::IntRect(32, 253, 186, 40));
			window.draw(optionTextS);
			optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default

			if (easyHard == 1) //hard
				optionTextS.setColor(sf::Color(255, 50, 50));
			optionTextS.setPosition(360, 60);
			optionTextS.setTextureRect(sf::IntRect(252, 253, 186, 40));
			window.draw(optionTextS);
			optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default
		}

		//Debug mode
		if (selected == debug)
			optionTextS.setColor(sf::Color(100, 100, 50));
		optionTextS.setPosition(60, 200);
		optionTextS.setTextureRect(sf::IntRect(10, 373, 514, 40));
		window.draw(optionTextS);
		optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default

		if (debugOffOn == 0) //off
			optionTextS.setColor(sf::Color(255, 50, 50));
		optionTextS.setPosition(120, 260);
		optionTextS.setTextureRect(sf::IntRect(36, 433, 146, 40));
		window.draw(optionTextS);
		optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default

		if (debugOffOn == 1) //on
			optionTextS.setColor(sf::Color(255, 50, 50));
		optionTextS.setPosition(300, 260);
		optionTextS.setTextureRect(sf::IntRect(250, 433, 109, 40));
		window.draw(optionTextS);
		optionTextS.setColor(sf::Color(255, 255, 255)); //set back to default

		break;
	};
}

void Menu::setGameState(int state)
{
	gameState = state; //change gamestate back to menu if user quit
}

int Menu::getInput(sf::RenderWindow& window, sf::Event& event, sf::Sound& menuSound, sf::Sound& menuSelectSound)
{
	keyDelayTime = keyDelayClock.getElapsedTime();
	float joyY1 = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	float joyY2 = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
	float joyY3 = sf::Joystick::getAxisPosition(2, sf::Joystick::Y);

	if (keyDelayTime.asMilliseconds() > 100 && (gameState == menu || gameState == options)) //delay cursor move, and prevent moving if not in main menu or options
	{
		if ((joyY1 == joyUp || joyY2 == joyUp || joyY3 == joyUp) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			menuSound.play();
			--selected;
		}
		else if ((joyY1 == joyDown || joyY2 == joyDown || joyY3 == joyDown) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			menuSound.play();
			++selected;
		}
		keyDelayClock.restart();
	}


	switch(gameState) //keep cursor within menu selections
	{
	case menu:
		if (selected < start)
			selected = quit;
		if (selected > quit)
			selected = start;
		break;

	case start:
		break;

	case options:
		if (selected < players)
			selected = debug;
		if (selected > debug)
			selected = players;
		break;

	case quit:
		break;
	};

		while (window.pollEvent(event))
		{
			int button = event.joystickButton.button;

		if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed)
		{
			if (button == Start || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) //select a menu option
			{
				switch (gameState)
				{
				case menu:
					menuSelectSound.play();
					gameState = selected;
					selected = start;

					//if selected options set selection to first option
					if (gameState == options)
						selected = players;

					break;

				case options:
					if (selected == players)
					{
						menuSelectSound.play();
						++numPlayers;
						if (numPlayers > 3)
							numPlayers = 1;
					}
					else if (selected == difficulty)
					{
						menuSelectSound.play();
						++easyHard;
						if (easyHard > 1)
							easyHard = 0;
					}
					else if (selected == debug)
					{
						menuSelectSound.play();
						++debugOffOn;
						if (debugOffOn > 1)
							debugOffOn = 0;
					}
					break;
				};
			}

			if (button == B || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //return to previous menu screen
			{
				menuSelectSound.play();
				selected = start;
				gameState = menu;
			}
		}
	}

	return gameState;
}

int Menu::getPlayers()
{
	return numPlayers;
}

int Menu::getDifficulty()
{
	return easyHard;
}

int Menu::getDebug()
{
	return debugOffOn;
}