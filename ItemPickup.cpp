#include "ItemPickup.h"


ItemPickup::ItemPickup()
{
}

void ItemPickup::createItem(sf::Vector2f coords)
{
	if ((std::rand() % 100 + 1) > 80) //20% chance
	{
		int type = std::rand() % 4; //randomly decide which item

		/*
		*less common items
		*ramdomize again if one of these
		*/
		if (type == homing)
			type = std::rand() % 4;
		if (type == dualGun)
			type = std::rand() % 4;

		if (type == missiles)
			items.push_back(Item(coords, type));
		if (type == homing)
			items.push_back(Item(coords, type));
		if (type == dualGun)
			items.push_back(Item(coords, type));
		if (type == healing)
			items.push_back(Item(coords, type));
	}
}

void ItemPickup::pickup(Players& players, sf::Sound& itemPickupSound)
{
	/*
	*collision with player to pickup item
	*then destroy specific item
	*/
	for (unsigned int i = 0; i < items.size(); ++i)
	{
		//player 1
		if (collision(players.playerBox1.getPosition(), players.playerBox1.getSize(), items.at(i).itemBox.getPosition(), items.at(i).itemBox.getSize()))
		{
			if (items.at(i).itemType == homing)
			{
				itemPickupSound.play();
				players.setGunType(homing, player1);
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == missiles)
			{
				itemPickupSound.play();
				players.incMissiles(player1); //add missiles to player
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == dualGun)
			{
				itemPickupSound.play();
				players.setGunType(dualGun, player1);
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == healing)
			{
				itemPickupSound.play();
				players.addHealth(player1);
				items.erase(items.begin() + i);
				continue;
			}
		}

		//player 2
		if (collision(players.playerBox2.getPosition(), players.playerBox2.getSize(), items.at(i).itemBox.getPosition(), items.at(i).itemBox.getSize()))
		{
			if (items.at(i).itemType == homing)
			{
				itemPickupSound.play();
				players.setGunType(homing, player2);
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == missiles)
			{
				itemPickupSound.play();
				players.incMissiles(player2); //add missiles to player
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == dualGun)
			{
				itemPickupSound.play();
				players.setGunType(dualGun, player2);
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == healing)
			{
				itemPickupSound.play();
				players.addHealth(player2);
				items.erase(items.begin() + i);
				continue;
			}
		}

		//player 3
		if (collision(players.playerBox3.getPosition(), players.playerBox3.getSize(), items.at(i).itemBox.getPosition(), items.at(i).itemBox.getSize()))
		{
			if (items.at(i).itemType == homing)
			{
				itemPickupSound.play();
				players.setGunType(homing, player3);
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == missiles)
			{
				itemPickupSound.play();
				players.incMissiles(player3); //add missiles to player
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == dualGun)
			{
				itemPickupSound.play();
				players.setGunType(dualGun, player3);
				items.erase(items.begin() + i);
				continue;
			}
			else if (items.at(i).itemType == healing)
			{
				itemPickupSound.play();
				players.addHealth(player3);
				items.erase(items.begin() + i);
				continue;
			}
		}
	}
}

void ItemPickup::render(sf::RenderWindow& window, sf::Sprite& itemS)
{
	itemS.setScale(1.5f, 1.5f);
	for (unsigned int i = 0; i < items.size(); ++i)
	{	
		switch (items.at(i).itemType)
		{
		case homing:
			itemS.setTextureRect(sf::IntRect(120, 59, 24, 12));
			itemS.setPosition(items.at(i).itemBox.getPosition());
			break;

		case missiles:
			itemS.setTextureRect(sf::IntRect(103, 3, 11, 20));
			itemS.setPosition(items.at(i).itemBox.getPosition());
			break;

		case dualGun:
			itemS.setTextureRect(sf::IntRect(49, 73, 23, 21));
			itemS.setPosition(items.at(i).itemBox.getPosition());
			break;

		case healing:
			itemS.setTextureRect(sf::IntRect(77, 6, 14, 14));
			itemS.setPosition(items.at(i).itemBox.getPosition());
			break;
		};
		window.draw(itemS);
	}
}

void ItemPickup::destroyItem(sf::View& view)
{
	for (unsigned int i = 0; i < items.size(); ++i)
	{
		if ((items.at(i).itemBox.getPosition().y - view.getCenter().y) > 500)
			items.erase(items.begin() + i);
	}
}