#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <string>
#include "Menu.h"
#include "Constants.h"
#include "Collision.h"

class Players
{
public:
	Players();
	void input(sf::View& view);
	void render(sf::RenderWindow& window, sf::Sprite planeS, sf::Sprite expS);
	void getFiring(bool& fire1, bool& fire2, bool& fire3, bool& missile1, bool& missile2, bool& missile3);
	void getXY(float& posX1, float& posY1, float& posX2, float& posY2, float& x3, float& y3);
	void kill(int playerNum);
	void useLife();
	bool getAlive(int playerNum);
	bool getInvincible(int playerNum);
	void changeInvincible();
	void setScore(int playerNum, int amount, sf::Sound& lifeUp);
	void reset();
	void nextLevelReset();
	void overheat(float& overheatAmount, bool& overheated, bool& fire, int gunType);
	void HUD(sf::RenderWindow& window, sf::View& view, sf::Sprite& hud, sf::Font& font); //head up display
	void setPlayers();
	sf::Vector2f getPlayerPos(int player);
	void subHealth(int hitAmount, int player);
	void addHealth(int player);
	int getHealth(int player);
	int getEquippedGunType(int player);
	void setGunType(int type, int player);
	void incMissiles(int player);
	void setLives(const int& player, const int& life);
	int getLives(const int& player);
	int getScore(const int& player);
	void lockScreenPos(bool lock);

	sf::RectangleShape playerBox1, playerBox2, playerBox3;
	
private:
	bool lockScreen;

	enum players{ player1, player2, player3 };
	float x1, y1, x2, y2, x3, y3; //player positions
	float x1Vel, y1Vel, x2Vel, y2Vel, x3Vel, y3Vel; //player velocities

	//gun heat level
	bool missile1, missile2, missile3; //missile fire
	bool fire1, fire2, fire3; //gun firing
	float overheat1, overheat2, overheat3; //gun overheat bar
	bool overheated1, overheated2, overheated3; //gun overheated
	sf::RectangleShape heatBar1, heatBar2, heatBar3; //heat bar UI

	//gun types
	int gunType1, gunType2, gunType3;
	enum gunTypes{machineGun, homing, dualGun};
	int bulletCount1, bulletCount2, bulletCount3; //after set amount of shots fired change gun back to machine gun

	//limit missile fire rate, total missiles
	sf::Time coolDownTime1, coolDownTime2, coolDownTime3;
	sf::Clock coolDownClock1, coolDownClock2, coolDownClock3;
	int numMissile1, numMissile2, numMissile3; //current missiles for player
	int bonusMissile1, bonusMissile2, bonusMissile3; //extra missile for player
	float missileCoolDown1, missileCoolDown2, missileCoolDown3;

	int player1PlaneType, player2PlaneType, player3PlaneType; //player plane type

	bool alive1, alive2, alive3; //alive state
	bool dead1, dead2, dead3; //player is dead
	int lives1, lives2, lives3; //player lives
	int health1, health2, health3; //player health

	int score1, score2, score3; //player score
	int showScore1, showScore2, showScore3; //show player score

	//invincible timers
	sf::Time invincibleTimer1;
	sf::Time invincibleTimer2;
	sf::Time invincibleTimer3;
	static sf::Clock invincibleClock1;
	static sf::Clock invincibleClock2;
	static sf::Clock invincibleClock3;

	bool invincible1, invincible2, invincible3; //make player plane invincible
	int flashInvincible; //flash planes when invincible

	//plane explosion animation
	int explodeFrameX;
	int explodeFrameY;
	void explodeAnimate(bool& dead);

	//objects
	Menu menu;
};

