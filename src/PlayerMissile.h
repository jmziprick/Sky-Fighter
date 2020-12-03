#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class PlayerMissile
{
public:
	PlayerMissile(float x, float y, int owner);
	void move();
	bool destroy(const sf::View& view);
	void render(sf::RenderWindow& window, sf::Sprite& smoke, sf::Sprite& missile);
	int getOwner();
	sf::Vector2f getPos();

	sf::RectangleShape missileBox;

private:
	void animate(); //smoke annimation and missile

	float x, y; //coords

	static int smokeFrame; //smoke frame number
	static int missileFrame; //missile frame number
	int missileOwner; //owner of each missile

	//smoke limit timer
	static sf::Clock smokeClock;
	sf::Time smokeTime;
};

