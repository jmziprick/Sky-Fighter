#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>
#include "Players.h"
#include "Collision.h"

class ItemPickup
{
public:
	ItemPickup();
	void createItem(sf::Vector2f coords);
	void pickup(Players& players, sf::Sound& itemPickupSound);
	void render(sf::RenderWindow& window, sf::Sprite& itemS);
	void destroyItem(sf::View& view);

private:
	struct Item
	{
		Item(sf::Vector2f pos, int itemType)
		{
			this->itemType = itemType;
			itemBox.setSize(sf::Vector2f(30, 30));
			itemBox.setPosition(pos);
		}

		int itemType;
		sf::RectangleShape itemBox;
	};

	std::vector<Item> items;

	enum types{ missiles, homing, dualGun, healing };

	enum players{player1, player2, player3};
};

