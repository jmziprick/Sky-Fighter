#pragma once
#include <SFML/Audio.hpp>
#include "Enemies.h"
#include "Players.h"
#include "Menu.h"

extern "C"
{
#include "LuaHeader/lualib.h"
#include  "LuaHeader/lauxlib.h"
}

class Boss1 : public Enemies
{
public:
	Boss1(float posX, float posY, Menu& menu, sf::Sound& alert);
	~Boss1();
	void move(sf::View& view, Players& players);
	void render(sf::RenderWindow& window, sf::Sprite bossS, sf::Sprite expS);
	bool getOffScreen(sf::View& view);
	bool fireGun();
	sf::Vector2f getCoords();

private:
	lua_State* lua; //lua interpreter

	//scripting timer
	sf::Time scriptTime;
	sf::Clock scriptClock;

	bool moveBack = false; //move boss back to top of screen
	int aliveStatus;

	int state;
	enum bossStates{fireState, stopState, resumeState, restartState, deadState};
};