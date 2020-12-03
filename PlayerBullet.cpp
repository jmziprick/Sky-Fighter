#include "PlayerBullet.h"


PlayerBullet::PlayerBullet(float x, float y, int owner, int bulletType)
{
	type = bulletType; //set what type of bullet

	//set bullet starting location
	this->x = x + 31;
	this->y = y;

	//bullet visual representation
	bullet.setPosition(this->x, this->y);
	bullet.setFillColor(sf::Color::Red);
	bullet.setOutlineColor(sf::Color::Black);
	bullet.setOutlineThickness(1.2f);
	bullet.setRadius(2.5f);

	//bullet bounding box for collision
	bulletBox.setSize(sf::Vector2f(4, 4));
	bulletBox.setFillColor(sf::Color::Red);
	bulletBox.setPosition(this->x, this->y);

	bulletOwner = owner; //set owner
}

void PlayerBullet::move(sf::Vector2f coords)
{
	//move bullet and bounding box using bullet's velocity

	//gun types
	switch (type)
	{
	case machineGun:
		y += BULLET_VEL;
		bullet.setPosition(x, y);
		bulletBox.setPosition(x, y);
		break;

	case homing:	
		if (coords != sf::Vector2f(0, 0))
		{
			if (x > (coords.x - 30))
				x += BULLET_VEL;
			else if (x < (coords.x - 30))
				x -= BULLET_VEL;
			if (y > (coords.y - 30))
				y += BULLET_VEL;
			else if (y < (coords.y - 30))
				y -= BULLET_VEL;

			bullet.setPosition(x, y);
			bulletBox.setPosition(x, y);
		}
		else
		{
			y += BULLET_VEL;
			bullet.setPosition(x, y);
			bulletBox.setPosition(x, y);
		}
		break;

	case dualGun:
		y += BULLET_VEL;
		bullet.setPosition(x, y);
		bulletBox.setPosition(x, y);
		break;
	};
}

bool PlayerBullet::destroy(const sf::View& view)
{
	/*
	*check if bullet has gone off screen
	*if true destroy bullet object
	*/
	bool destroyBullet = false;
	if (y - view.getCenter().y < -500)
		destroyBullet = true;

	//return if bullet is to be destroyed
	return destroyBullet; 
}

void PlayerBullet::render(sf::RenderWindow& window)
{
	//render bullet
	window.draw(bullet);
}

int PlayerBullet::getOwner()
{
	return bulletOwner;
}

sf::Vector2f PlayerBullet::getPos()
{
	sf::Vector2f pos(x, y);
	return pos;
}

int PlayerBullet::getType()
{
	return type;
}