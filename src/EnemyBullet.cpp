#include "EnemyBullet.h"


EnemyBullet::EnemyBullet(float x, float y)
{
	//regular bullet type

	//set bullet starting location
	this->x = x - 31;
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

	type = regular;
}

EnemyBullet::EnemyBullet(sf::Vector2f pos)
{
	//circular shot type

	//set bullet starting location
	x = pos.x += std::rand() % 40 - 30;
	y = pos.y += std::rand() % 40 - 30;

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

	float angle = (float)((std::rand() % 360) * 3.14 / 180.f);
	float speed = (float)(std::rand() % 3) + 6.5f;

	vel = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

	type = circular;
}

void EnemyBullet::move()
{
	switch (type)
	{
	case regular:
		//move bullet and bounding box using bullet's velocity
		y += ENEMY_BULLET_VEL;
		bullet.setPosition(x, y);
		bulletBox.setPosition(x, y);
		break;

	case circular:
		//bullets spread in circle velocities
		x += vel.x;
		y += vel.y;
		bullet.setPosition(x, y);
		bulletBox.setPosition(x, y);
		break;
	};
}

bool EnemyBullet::destroy(const sf::View& view)
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

void EnemyBullet::render(sf::RenderWindow& window)
{
	//render bullet
	window.draw(bullet);
}

sf::Vector2f EnemyBullet::getPos()
{
	sf::Vector2f pos(x, y);
	return pos;
}