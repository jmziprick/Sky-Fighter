#pragma once
#include <SFML/Graphics.hpp>
#include "EnemyPlanes.h"
#include "Constants.h"

class PlayerBullet
{
public:
	PlayerBullet(float x, float y, int owner, int bulletType);
	void move(sf::Vector2f coords);
	bool destroy(const sf::View& view);
	void render(sf::RenderWindow& window);
	int getOwner();
	int getType();
	sf::Vector2f getPos();

	sf::RectangleShape bulletBox;
	
private:
	float x, y;

	int bulletOwner; //owner of each bullet

	//gun types
	int type;
	enum types{machineGun, homing, dualGun};

	sf::CircleShape bullet;
};

