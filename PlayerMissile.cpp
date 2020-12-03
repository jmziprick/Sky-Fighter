#include "PlayerMissile.h"

sf::Clock PlayerMissile::smokeClock;
int PlayerMissile::smokeFrame = 0;
int PlayerMissile::missileFrame = 1;

PlayerMissile::PlayerMissile(float x, float y, int owner)
{
	//set missile starting location
	this->x = x - 31;
	this->y = y;

	//missile bounding box for collision
	missileBox.setSize(sf::Vector2f(4, 4));
	missileBox.setFillColor(sf::Color::Red);
	missileBox.setPosition(this->x, this->y);

	smokeFrame = 0; //set frame to 0

	missileOwner = owner; //set missile owner
}

void PlayerMissile::move()
{
	//move missile and bounding box using missile's velocity
	y += MISSILE_VEL;
	missileBox.setPosition(x, y);
}

bool PlayerMissile::destroy(const sf::View& view)
{
	/*
	*check if missile has gone off screen
	*if true destroy missile object
	*/
	bool destroyMissile = false;
	if (y - view.getCenter().y < -500)
		destroyMissile = true;

	//return if missile is to be destroyed
	return destroyMissile;
}

void PlayerMissile::render(sf::RenderWindow& window, sf::Sprite& smoke, sf::Sprite& missile)
{
	missile.setPosition(x, y);
	missile.setRotation(90);
	missile.setScale(sf::Vector2f(1.5f, .6f));
	missile.setTextureRect(sf::IntRect((52 * missileFrame) + 1, 0, 52, 25));

	smoke.setColor(sf::Color(255, 255, 255, 190));
	smoke.setRotation(-90);
	smoke.setScale(sf::Vector2f(.5f, .5f));
	smoke.setPosition(x - 20, y + 160);
	smoke.setTextureRect(sf::IntRect(0, 50 * smokeFrame, 205, 50));
	animate();

	//render missile
	window.draw(missile);
	window.draw(smoke);
}

void PlayerMissile::animate()
{
	smokeTime = smokeClock.getElapsedTime();

	if (smokeFrame > 3)
		smokeFrame = 0;

	if (smokeTime.asMilliseconds() > SMOKE_FRAME_RATE)
	{
		++smokeFrame;
		++missileFrame;
		smokeClock.restart();
	}

	if (missileFrame > 3)
		missileFrame = 1;
}

int PlayerMissile::getOwner()
{
	return missileOwner;
}

sf::Vector2f PlayerMissile::getPos()
{
	sf::Vector2f pos(x, y);
	return pos;
}