#include "Boss1.h"


Boss1::Boss1(float posX, float posY, Menu& menu, sf::Sound& alert)
{
	alert.play();

	//set starting position
	x = posX;
	y = posY;

	//bounding box
	enemyBox.setSize(sf::Vector2f(400, 150));
	enemyBox.setPosition(x, y + 160);

	alive = true; //enemy alive
	dead = false; //enemy dead

	//set explosion frame to 0
	explodeFrameX = 0;
	explodeFrameY = 0;

	fire = false; //set firing gun to false

	//plane direction
	direction = rand() % 2;

	//set plane move type
	moveType = 1;

	//set health
	if (menu.getDifficulty() == 0)
		health = BOSS1_HEALTH + (menu.getPlayers() - 1) * 800; //scale health depending on how many players there are active
	else if (menu.getDifficulty() == 1)
		health = BOSS1_HEALTH_HARD + (menu.getPlayers() - 1) * 800; //scale health depending on how many players there are active

	//init script file
	lua = lua_open();
	luaL_openlibs(lua);
	luaL_dofile(lua, "Scripts/boss1.lua");

	moveBack = false;
	aliveStatus = 1;
}

Boss1::~Boss1()
{
	lua_close(lua);
	lua = NULL;
}

void Boss1::move(sf::View& view, Players& players)
{
	scriptTime = scriptClock.getElapsedTime();
	int currentTime = (int)(scriptTime.asSeconds());

	if (alive == false)
		aliveStatus = 0;

	lua_getglobal(lua, "move"); //function name

	//arguements
	lua_pushnumber(lua, x);
	lua_pushnumber(lua, y);
	lua_pushnumber(lua, currentTime);
	lua_pushnumber(lua, aliveStatus);

	lua_call(lua, 4, 1); //call function with 3 args and 1 return

	state = (int)lua_tointeger(lua, -1); //get result
	lua_pop(lua, 1); //remove from stack

	switch (state)
	{
	case fireState:
		y += MOVE_SPEED; //keep boss moving at same rate as scrolling speed

		/*
		*if boss has gone too far on +y move up screen
		*if boss has gone too far on -y stop moving up screen
		*/
		if (moveBack)
			y += MOVE_SPEED * 6;
		if (y - view.getCenter().y > 300) //+y bottom screen
			moveBack = true;
		else if (view.getCenter().y - y > 600) //-y top screen
			moveBack = false;

		if (direction == left)
			x -= ENEMY_X_VEL;
		else if (direction == right)
			x += ENEMY_X_VEL;

		if (x - view.getCenter().x > 300) //switch direction to left if too far right
			direction = left;
		if (view.getCenter().x - x > 500) //switch direction to right if too far left
			direction = right;
		break;

	case stopState:
		y += ENEMY_Y_VEL * 2;
		break;

	case resumeState:
		y -= 10;
		break;

	case restartState:
		scriptClock.restart();
		break;

	case deadState:
		y += ENEMY_Y_VEL; //move off screen if dead
		break;
	};

	if (view.getCenter().y <= 2200)
	{
		//do super attack
		//mission failed
		/*for (int i = 0; i < 3; ++i)
		{
			//take all lives away and kill players
			players.setLives(i, -players.getLives(i));
			players.kill(i);

			//lose game
		}*/
	}

	enemyBox.setPosition(x, y + 160); //set bounding box
}

void Boss1::render(sf::RenderWindow& window, sf::Sprite bossS, sf::Sprite expS)
{
	//boss plane
	bossS.setScale(2.5f, 2.5f);
	bossS.setPosition(sf::Vector2f(x, y));
	bossS.setTextureRect(sf::IntRect(9, 6, 162, 143));
	window.draw(bossS);

	//boss plane undamaged
	if (alive == true)
	{
		bossS.setScale(2.5f, 2.5f);
		bossS.setPosition(sf::Vector2f(x, y + 195));
		bossS.setTextureRect(sf::IntRect(181, 12, 162, 66));
		window.draw(bossS);
	}

	//boss plane shaddow
	bossS.setScale(1.5f, 1.5f);
	bossS.setColor(sf::Color(255, 255, 255, 100));
	bossS.setPosition(sf::Vector2f(x + 80, y + 330));
	bossS.setTextureRect(sf::IntRect(35, 156, 110, 99));
	window.draw(bossS);

	//died
	if (alive == false && dead == false)
	{
		expS.setScale(4.f, 4.f);
		expS.setRotation(180);
		expS.setPosition((x + 400), (y + 300));
		expS.setTextureRect(sf::IntRect(100 * explodeFrameX, 100 * explodeFrameY, 100, 100));
		explodeAnimate(alive, dead);
		window.draw(expS);
	}
}

bool Boss1::getOffScreen(sf::View& view)
{
	if (y - view.getCenter().y > 700)
		return true;
	else
		return false;
}

sf::Vector2f Boss1::getCoords()
{
	sf::Vector2f coords;
	coords.x = x + 250;
	coords.y = y + 250;

	return coords;
}

bool Boss1::fireGun()
{
	gunTime = gunClock.getElapsedTime();

	if (state == fireState)
	{
		//sets fire rate
		if (menu.getDifficulty() == 0) //easy
		{
			if (gunTime.asMilliseconds() > ENEMY_FIRE_RATE && alive == true)
			{
				fire = true;
				gunClock.restart();
			}
			else
				fire = false;
		}
		else if (menu.getDifficulty() == 1 && alive == true) //hard
		{
			if (gunTime.asMilliseconds() > ENEMY_FIRE_RATE - 200)
			{
				fire = true;
				gunClock.restart();
			}
			else
				fire = false;
		}
	}

	return fire;
}