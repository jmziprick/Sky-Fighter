#include "Boss2.h"


Boss2::Boss2(float posX, float posY, Menu& menu, sf::Sound& alert)
{
	alert.play();

	//set starting position
	x = posX;
	y = posY;

	//bounding box
	enemyBox.setSize(sf::Vector2f(65, 600));
	enemyBox.setPosition(x - 70, y + 40);

	alive = true; //enemy alive
	dead = false; //enemy dead

	//set explosion frame to 0
	explodeFrameX = 0;
	explodeFrameY = 0;

	fire = false; //set firing gun to false
	preFire = false; //set first pre fire shot to false

	//set health
	if(menu.getDifficulty() == 0)
		health = BOSS2_HEALTH + (menu.getPlayers() - 1) * 800; //scale health depending on how many players there are active
	else if (menu.getDifficulty() == 1)
		health = BOSS2_HEALTH_HARD + (menu.getPlayers() - 1) * 800; //scale health depending on how many players there are active
}

void Boss2::move(sf::View& view, Players& players)
{
	enemyBox.setPosition(x - 70, y + 60);
}

void Boss2::render(sf::RenderWindow& window, sf::Sprite bossS, sf::Sprite expS)
{
	//boss ship
	bossS.setScale(.5f, .5f);
	bossS.setRotation(90);
	bossS.setPosition(sf::Vector2f(x, y));
	bossS.setTextureRect(sf::IntRect(3, 3, 1367, 162));
	window.draw(bossS);

	//top gun
	//boss gun
	bossS.setScale(.6f, .6f);
	bossS.setRotation(90);
	bossS.setPosition(sf::Vector2f(x - 15, y + 130));
	bossS.setTextureRect(sf::IntRect(5, 485, 77, 77));
	window.draw(bossS);

	//boss gun turret left
	bossS.setScale(.6f, .6f);
	bossS.setRotation(90);
	bossS.setPosition(sf::Vector2f(x - 40, y + 170));
	bossS.setTextureRect(sf::IntRect(267, 630, 57, 14));
	window.draw(bossS);

	//boss gun turret right
	bossS.setScale(.6f, .6f);
	bossS.setRotation(90);
	bossS.setPosition(sf::Vector2f(x - 27, y + 170));
	bossS.setTextureRect(sf::IntRect(267, 630, 57, 14));
	window.draw(bossS);

	//bottom gun
	//boss gun
	bossS.setScale(.6f, .6f);
	bossS.setRotation(90);
	bossS.setPosition(sf::Vector2f(x - 15, y + 480));
	bossS.setTextureRect(sf::IntRect(5, 485, 77, 77));
	window.draw(bossS);

	//boss gun turret left
	bossS.setScale(.6f, .6f);
	bossS.setRotation(90);
	bossS.setPosition(sf::Vector2f(x - 40, y + 519));
	bossS.setTextureRect(sf::IntRect(267, 630, 57, 14));
	window.draw(bossS);

	//boss gun turret right
	bossS.setScale(.6f, .6f);
	bossS.setRotation(90);
	bossS.setPosition(sf::Vector2f(x - 27, y + 519));
	bossS.setTextureRect(sf::IntRect(267, 630, 57, 14));
	window.draw(bossS);

	//died
	if (alive == false && dead == false)
	{
		expS.setScale(4.f, 4.f);
		expS.setRotation(180);
		expS.setPosition((x + 200), (y + 450));
		expS.setTextureRect(sf::IntRect(100 * explodeFrameX, 100 * explodeFrameY, 100, 100));
		explodeAnimate(alive, dead);
		window.draw(expS);
	}
}

bool Boss2::fireGun()
{
	gunTime = gunClock.getElapsedTime();

	//sets fire rate
	if (menu.getDifficulty() == 0) //easy
	{
		if (gunTime.asMilliseconds() > BOSS_FIRE_RATE - 450 && preFire == true && alive == true)
		{
			fire = true;
			preFire = false;
		}
		else if (gunTime.asMilliseconds() > BOSS_FIRE_RATE && alive == true)
		{
			fire = true;
			preFire = true;
			gunClock.restart();
		}
		else
			fire = false;
	}
	else if (menu.getDifficulty() == 1 && alive == true) //hard
	{
		if (gunTime.asMilliseconds() > BOSS_FIRE_RATE_HARD - 450 && preFire == true && alive == true)
		{
			fire = true;
			preFire = false;
		}
		else if (gunTime.asMilliseconds() > BOSS_FIRE_RATE_HARD && alive == true)
		{
			fire = true;
			preFire = true;
			gunClock.restart();
		}
		else
			fire = false;
	}

	return fire;
}

bool Boss2::getOffScreen(sf::View& view)
{
	if (y - view.getCenter().y > 700)
		return true;
	else
		return false;
}

sf::Time Boss2::getGunTime()
{
	return gunTime;
}