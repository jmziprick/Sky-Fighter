#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"

/*
*NOTE
*background image must be resolution size 1000 x 800
*/

class Menu
{
public:
	Menu();
	void render(sf::RenderWindow& window, sf::Sprite& backgroundS, sf::Sprite& menuTextS, sf::Sprite& optionTextS, sf::Font& font);
	int getInput(sf::RenderWindow& window, sf::Event& event, sf::Sound& menuSound, sf::Sound& menuSelectSound);
	void setGameState(int state);
	int getPlayers();
	int getDifficulty();
	int getDebug();

private:
	int selected; //selected menu item
	enum selections{menu, start, options, quit};
	enum optionSelections{players, difficulty, debug};
	static int numPlayers;
	static int easyHard;
	int debugOffOn;

	int gameState;

	sf::Clock keyDelayClock;
	sf::Time keyDelayTime;
};

