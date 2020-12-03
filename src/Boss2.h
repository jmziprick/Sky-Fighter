#pragma once
#include <SFML/Audio.hpp>
#include "Enemies.h"
#include "Players.h"
#include "Menu.h"

class Boss2 : public Enemies
{
public:
	Boss2(float posX, float posY, Menu& menu, sf::Sound& alert);
	void move(sf::View& view, Players& players);
	void render(sf::RenderWindow& window, sf::Sprite bossS, sf::Sprite expS);
	bool getOffScreen(sf::View& view);
	bool fireGun();
	sf::Time getGunTime();

private:
	bool preFire;
};