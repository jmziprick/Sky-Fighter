#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class EnemyBullet
{
public:
	EnemyBullet(float x, float y);
	EnemyBullet(sf::Vector2f pos);
	void move();
	bool destroy(const sf::View& view);
	void render(sf::RenderWindow& window);
	sf::Vector2f getPos();

	sf::RectangleShape bulletBox;

private:
	float x, y;

	int type;
	enum types{regular, circular};
	
	sf::Vector2f vel;

	sf::CircleShape bullet;
};

