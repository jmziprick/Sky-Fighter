#pragma once
#include "Enemies.h"
#include "Menu.h"

class EnemyPlanes : public Enemies
{
public:
	EnemyPlanes(const sf::View& view, Menu& menu);
	void loopPlaneBack(sf::View& view);
	void move(sf::View& view);
};

