#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Menu.h"
#include "Constants.h"

/*
*Parent Class for all enemy type objects.  Class was chosen
*to ensure protection of the multiple data types
*/
class Enemies
{
public:
	Enemies();
	Enemies(const sf::View& view);
	void move(sf::View& view);
	void render(sf::RenderWindow& window, sf::Sprite EnemyS, sf::Sprite expS);
	void kill();
	bool getDead();
	bool getAlive();
	bool fireGun();
	sf::Vector2f getCoords();
	void subHealth(int hitAmount);
	int getHealth();
	int getScoreAmount();

	sf::RectangleShape enemyBox;

/*
*Proctected was chosen over private in order 
*to provide subclasses
*easier access to the data
*/
protected:
	float x, y; //position
	enum directions{ left, right };
	int direction; //current plane direction
	int moveType; //moveType plane will change direction from left and right, where non moveType will always fly straight

	int planeType;
	enum planeTypes{ mig51s, su37k, mig51 };
	int scoreAmount; //enemy score value

	int health;

	bool alive; //alive state
	bool dead; //enemy is dead

	//enemy gun limit timer
	sf::Clock gunClock;
	sf::Time gunTime;

	bool fire; //firing gun

	//explosion animation
	int explodeFrameX;
	int explodeFrameY;
	void explodeAnimate(bool& alive, bool& dead);

	//objects
	Menu menu;
};