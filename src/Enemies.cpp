#include "Enemies.h"

Enemies::Enemies()
{
	//set starting position
	x = 0;
	y = 0;

	scoreAmount = 0;

	//bounding box
	if (planeType == mig51s)
	{
		enemyBox.setSize(sf::Vector2f(65, 115));
		enemyBox.setPosition(x - 65, y - 115);
	}
	else if (planeType == su37k)
	{
		enemyBox.setSize(sf::Vector2f(65, 115));
		enemyBox.setPosition(x - 90, y - 120);
	}
	else if (planeType == mig51)
	{
		enemyBox.setSize(sf::Vector2f(65, 115));
		enemyBox.setPosition(x - 85, y - 135);
	}

	alive = true; //enemy alive
	dead = false; //enemy dead

	//set explosion frame to 0
	explodeFrameX = 0;
	explodeFrameY = 0;

	fire = false; //set firing gun to false

	//direction
	direction = rand() % 2;

	//set enemy move type
	moveType = rand() % 2;

	//set health
	health = 0;
}

void Enemies::move(sf::View& view)
{
	y += ENEMY_Y_VEL;

	//if enemy is move type, change flying direction back and forth
	enum type { no, yes };
	if (moveType == yes)
	{
		if (direction == left)
			x -= ENEMY_X_VEL;
		else if (direction == right)
			x += ENEMY_X_VEL;
	}

	if (x - view.getCenter().x > 550) //switch direction to left if too far right
		direction = left;
	if (view.getCenter().x - x > 480) //switch direction to right if too far left
		direction = right;

	if (planeType == mig51s)	
		enemyBox.setPosition(x - 65, y - 115);
	else if (planeType == su37k)
		enemyBox.setPosition(x - 100, y - 125);
	else if (planeType == mig51)
		enemyBox.setPosition(x - 100, y - 150);
}

void Enemies::render(sf::RenderWindow& window, sf::Sprite enemyS, sf::Sprite expS)
{
	if (planeType == mig51s)
	{
		//plane
		enemyS.setScale(sf::Vector2f(.6f, .6f));
		enemyS.setPosition(sf::Vector2f(x, y));
		enemyS.setTextureRect(sf::IntRect(34, 5, 111, 201));
		enemyS.setColor(sf::Color(255, 255, 255, 255));
		enemyS.setRotation(180);
		if (alive == true)
			window.draw(enemyS);

		//plane shaddow
		enemyS.setScale(sf::Vector2f(.3f, .3f));
		enemyS.setPosition(sf::Vector2f(x - 50, y + 30));
		enemyS.setTextureRect(sf::IntRect(34, 403, 111, 201));
		enemyS.setColor(sf::Color(255, 255, 255, 80));
		enemyS.setRotation(180);
		if (alive == true)
			window.draw(enemyS);
	}
	else if (planeType == su37k)
	{
		//plane
		enemyS.setScale(sf::Vector2f(.7f, .8f));
		enemyS.setPosition(sf::Vector2f(x, y));
		enemyS.setTextureRect(sf::IntRect(692, 19, 115, 165));
		enemyS.setColor(sf::Color(255, 255, 255, 255));
		enemyS.setRotation(180);
		if (alive == true)
			window.draw(enemyS);

		//plane shaddow
		enemyS.setScale(sf::Vector2f(.4f, .5f));
		enemyS.setPosition(sf::Vector2f(x - 50, y + 30));
		enemyS.setTextureRect(sf::IntRect(692, 419, 115, 165));
		enemyS.setColor(sf::Color(255, 255, 255, 80));
		enemyS.setRotation(180);
		if (alive == true)
			window.draw(enemyS);
	}

	else if (planeType == mig51)
	{
		//plane
		enemyS.setScale(sf::Vector2f(.7f, .8f));
		enemyS.setPosition(sf::Vector2f(x, y));
		enemyS.setTextureRect(sf::IntRect(174, 8, 111, 194));
		enemyS.setColor(sf::Color(255, 255, 255, 255));
		enemyS.setRotation(180);
		if (alive == true)
			window.draw(enemyS);

		//plane shaddow
		enemyS.setScale(sf::Vector2f(.4f, .5f));
		enemyS.setPosition(sf::Vector2f(x - 50, y + 30));
		enemyS.setTextureRect(sf::IntRect(174, 409, 111, 194));
		enemyS.setColor(sf::Color(255, 255, 255, 80));
		enemyS.setRotation(180);
		if (alive == true)
			window.draw(enemyS);
	}

	//died
	if (alive == false && dead == false)
	{
		expS.setRotation(180);
		expS.setPosition(x, y);
		expS.setTextureRect(sf::IntRect(100 * explodeFrameX, 100 * explodeFrameY, 100, 100));
		explodeAnimate(alive, dead);
		window.draw(expS);
	}
}

bool Enemies::fireGun()
{
	gunTime = gunClock.getElapsedTime();

	//sets fire rate
	if (gunTime.asMilliseconds() > ENEMY_FIRE_RATE && alive == true)
	{
		fire = true;
		gunClock.restart();
	}
	else
		fire = false;

	return fire;
}

void Enemies::explodeAnimate(bool& alive, bool& dead)
{
	if (explodeFrameX > 9)
	{
		++explodeFrameY;
		explodeFrameX = 0;
	}

	if (explodeFrameY == 8 && explodeFrameX > 2)
	{
		explodeFrameX = 0;
		explodeFrameY = 0;
		dead = true;
	}

	++explodeFrameX;
}

void Enemies::kill()
{
	alive = false; //sets alive state to false
}

bool Enemies::getDead()
{
	return dead;
}

bool Enemies::getAlive()
{
	return alive;
}

sf::Vector2f Enemies::getCoords()
{
	sf::Vector2f coords;
	coords.x = x;
	coords.y = y;

	return coords;
}

void Enemies::subHealth(int hitAmount)
{
	health -= hitAmount;
}

int Enemies::getHealth()
{
	return health;
}

int Enemies::getScoreAmount()
{
	return scoreAmount;
}