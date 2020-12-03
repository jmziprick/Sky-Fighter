#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sfeMovie/Movie.hpp>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include "SplashScreen.h"
#include "MusicPlayer.h"
#include "Menu.h"
#include "Tiles.h"
#include "Players.h"
#include "EnemyPlanes.h"
#include "Boss1.h"
#include "Boss2.h"
#include "PlayerMissile.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Collision.h"
#include "Particle.h"
#include "Icon.h"
#include "ItemPickup.h"
#include "Distance.h"
#include "Credits.h"
#include "Constants.h"

class Game
{
public:
	Game();
	void loadLevel();
	void update();
	void updateGraphics();
	void checkCollisions();
	void init();
	void moveScreen();
	void playerFireGun();
	void enemyFireGun();
	void createEnemies();
	void reset();
	void nextLevelReset();
	int mainMenu();
	int optionMenu();
	int getDebug();
	void showDebug(int fps);
	void spawnBoss();
	void killBoss();
	int checkPlayerWinLose();
	void currentMusic();
	bool splashScreen();
	
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::View view;
	sf::View menuView;
	bool lockScreen;

	static int gameState;
	static int levelState; //level 0 main menu, level 1 after game levels

	enum playersNum{ player1, player2, player3 }; //players

	//win and lose
	bool lose;
	bool win;
	bool completedGame;

	sf::Clock completedGameClock;
	sf::Time completedGameTime;
	sf::Clock loseClock;
	sf::Time loseTime;
	sf::Clock winClock;
	sf::Time winTime;

	//boss
	bool createBoss;
	bool killedBoss;
	sf::Time bossTextTime;
	sf::Clock bossTextClock;

	//all players machine gun limit timer
	sf::Clock gunClock;
	sf::Time gunTime;

	//timer to create new enemy planes
	sf::Time newEnemyPlanetime;
	sf::Clock newEnemyPlaneclock;

	//timer to prevent enemies at start of new game
	sf::Time noEnemyTimer;
	sf::Clock noEnemyClock;
	bool noEnemies;

	//gun sound delay
	sf::Clock gunSoundClock;
	sf::Time gunSoundTime;

	//hit sound delay
	sf::Clock hitSoundClock;
	sf::Time hitSoundTime;

	bool startMusic;

	//credit position scroll
	float creditPos;

	//sprites

	//splash
	sf::Sprite splashS;
	sf::Texture splashT;

	//tilemap
	sf::Sprite tileS;
	sf::Texture tileT;

	//planes
	sf::Sprite planeS;
	sf::Texture planeT;

	//tank
	sf::Sprite tankS;
	sf::Texture tankT;

	//boss1
	sf::Sprite boss1S;
	sf::Texture boss1T;

	//boss2
	sf::Sprite boss2S;
	sf::Texture boss2T;

	//explosion
	sf::Sprite expS;
	sf::Texture expT;

	//smoke
	sf::Sprite smokeS;
	sf::Texture smokeT;

	//missile
	sf::Sprite missileS;
	sf::Texture missileT;

	//item icons
	sf::Sprite itemS;
	sf::Texture itemT;

	//menu background
	sf::Sprite backgroundS;
	sf::Texture backgroundT;

	//win screen
	sf::Sprite winScreenS;
	sf::Texture winScreenT;

	//menu text
	sf::Sprite menuTextS;
	sf::Texture menuTextT;

	//option text
	sf::Sprite optionTextS;
	sf::Texture optionTextT;

	//HUD
	sf::Sprite hudS;
	sf::Texture hudT;

	//font
	sf::Font font;

	//text
	sf::Text showFps;
	sf::Text gameOver;
	sf::Text mssionComplete;
	sf::Text bossAproaching;
	sf::Text winEasy;
	sf::Text winHard;
	sf::Text credits;
	sf::Text creditsEnding;
	sf::Text pushStart;

	//video

	sfe::Movie openingMovie;

	//sounds

	//splash
	sf::Sound splashSound;
	sf::SoundBuffer splashBuff;

	//menu sound
	sf::Sound menuSound;
	sf::SoundBuffer menuBuff;

	//menu sound
	sf::Sound menuSelectSound;
	sf::SoundBuffer menuSelectBuff;

	//explosion
	sf::Sound explodeSound;
	sf::SoundBuffer explodeBuff;

	//die explosion
	sf::Sound dieExplodeSound;
	sf::SoundBuffer dieExplodeBuff;

	//machine gun
	sf::Sound gunSound;
	sf::SoundBuffer gunBuff;

	//heavy gun
	sf::Sound heavyGunSound;
	sf::SoundBuffer heavyGunBuff;

	//missile explosion
	sf::Sound missileExplodeSound;
	sf::SoundBuffer missileExplodeBuff;

	//missile
	sf::Sound missileSound;
	sf::SoundBuffer missileBuff;

	//hit
	sf::Sound hitSound;
	sf::SoundBuffer hitBuff;

	//hit1
	sf::Sound hitSound1;
	sf::SoundBuffer hitBuff1;

	//item pickup
	sf::Sound itemPickupSound;
	sf::SoundBuffer itemPickupBuff;

	//alert
	sf::Sound alertSound;
	sf::SoundBuffer alertBuff;

	//boss explode
	sf::Sound bossExpSound;
	sf::SoundBuffer bossExpBuff;

	//life up
	sf::Sound lifeUpSound;
	sf::SoundBuffer lifeUpBuff;

	//MUSIC
	sf::Music music;
	sf::Music endingMusic;

	//objects
	SplashScreen splash;
	Menu menu;
	MusicPlayer musicPlayer;
	Tiles tiles;
	Players players;
	Particle particle;
	ItemPickup itemPickup;
	Boss1* boss1 = NULL;
	Boss2* boss2 = NULL;

	static std::vector<PlayerMissile*> playerMissiles;
	static std::vector<PlayerBullet*> playerBullets;
	static std::vector<EnemyBullet*> enemyBullets;
	static std::vector<EnemyPlanes*> enemyPlanes;
};