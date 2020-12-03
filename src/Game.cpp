#include "Game.h"


std::vector<PlayerMissile*> Game::playerMissiles;
std::vector<PlayerBullet*> Game::playerBullets;
std::vector<EnemyBullet*> Game::enemyBullets;
std::vector<EnemyPlanes*> Game::enemyPlanes;

int Game::levelState = 0; //level
int Game::gameState = 0; //set to main menu

Game::Game()
{
	window.create(sf::VideoMode(1280, 720), "Game", sf::Style::Resize | sf::Style::Titlebar);
	window.setKeyRepeatEnabled(false);
	window.setIcon(SF_ICON.width, SF_ICON.height, SF_ICON.pixel_data);

	view.setCenter(500, VIEW_START_LOCATION);
	menuView.setCenter(200, 0);

	window.setView(view);
	window.setMouseCursorVisible(false);

	//set sound levels
	gunSound.setVolume(50);
	heavyGunSound.setVolume(60);
	music.setVolume(65);
	endingMusic.setVolume(80);
	hitSound.setVolume(70);
	hitSound1.setVolume(70);
	itemPickupSound.setVolume(100);
	alertSound.setVolume(50);
	lifeUpSound.setVolume(60);
	bossExpSound.setVolume(50);

	noEnemies = true;
	startMusic = true;
	createBoss = false;
	killedBoss = false;
	lose = false;
	win = false;
	completedGame = false;
	lockScreen = false;

	creditPos = 0;
}

bool Game::splashScreen()
{
	window.clear();

	window.setView(menuView);

	bool continueScreen = splash.display(window, splashS, splashSound, openingMovie);

	window.display();
	window.setFramerateLimit(FPS);

	return continueScreen;
}

void Game::init()
{
	/*
	*load textures and set sprites
	*quit program if resource file not found
	*/
	if (!splashT.loadFromFile("Splash/splash.png"))
	{
		window.close();
		MessageBox(0, "Unable to load splash.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	splashS.setTexture(splashT);

	if (!tileT.loadFromFile("Images/tiles.png"))
	{
		window.close();
		MessageBox(0, "Unable to load tiles.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}

	if (!planeT.loadFromFile("Images/planes.png"))
	{
		window.close();
		MessageBox(0, "Unable to load planes.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	planeS.setTexture(planeT);

	if (!tankT.loadFromFile("Images/tank.png"))
	{
		window.close();
		MessageBox(0, "Unable to load tank.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	tankS.setTexture(tankT);

	if (!boss1T.loadFromFile("Images/boss1.png"))
	{
		window.close();
		MessageBox(0, "Unable to load boss1.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	boss1S.setTexture(boss1T);

	if (!boss2T.loadFromFile("Images/boss2.png"))
	{
		window.close();
		MessageBox(0, "Unable to load boss2.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	boss2S.setTexture(boss2T);

	if (!expT.loadFromFile("Images/explosion.png"))
	{
		window.close();
		MessageBox(0, "Unable to load explosion.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	expS.setTexture(expT);

	if (!smokeT.loadFromFile("Images/smoke.png"))
	{
		window.close();
		MessageBox(0, "Unable to load smoke.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	smokeS.setTexture(smokeT);

	if (!missileT.loadFromFile("Images/missile.png"))
	{
		window.close();
		MessageBox(0, "Unable to load missile.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	missileS.setTexture(missileT);

	if (!itemT.loadFromFile("Images/item icons.png"))
	{
		window.close();
		MessageBox(0, "Unable to load item icons.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	itemS.setTexture(itemT);

	if (!backgroundT.loadFromFile("Images/menu.png"))
	{
		window.close();
		MessageBox(0, "Unable to load menu.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	backgroundS.setTexture(backgroundT);

	if (!menuTextT.loadFromFile("Images/menu1.png"))
	{
		window.close();
		MessageBox(0, "Unable to load menu1.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	menuTextS.setTexture(menuTextT);

	if (!optionTextT.loadFromFile("Images/menu2.png"))
	{
		window.close();
		MessageBox(0, "Unable to load menu2.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	optionTextS.setTexture(optionTextT);

	if (!hudT.loadFromFile("Images/UI.png"))
	{
		window.close();
		MessageBox(0, "Unable to load UI.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	hudS.setTexture(hudT);

	if (!winScreenT.loadFromFile("Images/win screen.png"))
	{
		window.close();
		MessageBox(0, "Unable to load win screen.png", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	winScreenS.setTexture(winScreenT);

	if (!font.loadFromFile("Images/font.ttf"))
	{
		window.close();
		MessageBox(0, "Unable to load font.ttf", "Error loading resource", MB_ICONERROR);
		exit(1);
	}

	//load video
	if (!openingMovie.openFromFile("Splash/opening video.wmv"))
	{
		window.close();
		MessageBox(0, "Unable to load opening video.wmv", "Error loading resource", MB_ICONERROR);
		exit(1);
	}

	//load sounds
	if (!splashBuff.loadFromFile("Sound/splash.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load splash.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	splashSound.setBuffer(splashBuff);

	if (!menuBuff.loadFromFile("Sound/blip.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load blip.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	menuSound.setBuffer(menuBuff);

	if (!menuSelectBuff.loadFromFile("Sound/blip 2.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load blip 2.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	menuSelectSound.setBuffer(menuSelectBuff);

	if (!explodeBuff.loadFromFile("Sound/explode.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load explode.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	explodeSound.setBuffer(explodeBuff);

	if (!dieExplodeBuff.loadFromFile("Sound/died explode.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load died explode.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	dieExplodeSound.setBuffer(dieExplodeBuff);

	if (!gunBuff.loadFromFile("Sound/machine gun.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load machine gun.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	gunSound.setBuffer(gunBuff);

	if (!heavyGunBuff.loadFromFile("Sound/heavy gun.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load heavy gun.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	heavyGunSound.setBuffer(heavyGunBuff);

	if (!missileBuff.loadFromFile("Sound/missile.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load missile.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	missileSound.setBuffer(missileBuff);

	if (!missileExplodeBuff.loadFromFile("Sound/missile explode.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load missile explode.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	missileExplodeSound.setBuffer(missileExplodeBuff);
	
	if (!hitBuff.loadFromFile("Sound/hit.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load hit.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	hitSound.setBuffer(hitBuff);

	if (!hitBuff1.loadFromFile("Sound/hit1.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load hit1.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	hitSound1.setBuffer(hitBuff1);

	if (!itemPickupBuff.loadFromFile("Sound/item pickup.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load item pickup.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	itemPickupSound.setBuffer(itemPickupBuff);

	if (!alertBuff.loadFromFile("Sound/alert.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load alert.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	alertSound.setBuffer(alertBuff);

	if (!bossExpBuff.loadFromFile("Sound/boss explode.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load boss explode.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	bossExpSound.setBuffer(bossExpBuff);

	if (!lifeUpBuff.loadFromFile("Sound/life up.wav"))
	{
		window.close();
		MessageBox(0, "Unable to load life up.wav", "Error loading resource", MB_ICONERROR);
		exit(1);
	}
	lifeUpSound.setBuffer(lifeUpBuff);


	//text

	//boss warning
	bossAproaching.setCharacterSize(25);
	bossAproaching.setFont(font);
	bossAproaching.setColor(sf::Color::Red);
	bossAproaching.setString("\tWARNING\nBoss approaching");


	//game over
	gameOver.setFont(font);
	gameOver.setCharacterSize(55);
	gameOver.setColor(sf::Color::Red);
	gameOver.setString("MISSION FAILED\n\n\n\tGame Over");


	//mission completed
	mssionComplete.setFont(font);
	mssionComplete.setCharacterSize(55);
	mssionComplete.setColor(sf::Color::Red);
	mssionComplete.setString("MISSION COMPLETED\n\n\tReturning to base.");

	//ending credits
	winEasy.setFont(font);
	winEasy.setCharacterSize(50);
	winEasy.setColor(sf::Color::Red);

	winHard.setFont(font);
	winHard.setCharacterSize(50);
	winHard.setColor(sf::Color::Red);

	pushStart.setFont(font);
	pushStart.setCharacterSize(60);
	pushStart.setColor(sf::Color::Green);
	pushStart.setString("Push Start");

	creditsEnding.setString(endingCredits);
	creditsEnding.setFont(font);
	creditsEnding.setColor(sf::Color::Red);
	creditsEnding.setCharacterSize(35);
}

void Game::loadLevel()
{
	int tileType = 0;
	int map[LEVEL_HEIGHT][LEVEL_WIDTH];

	int tileX = 0;
	int tileY = 0;

	std::ifstream load;

	switch (levelState)
	{
	case 0: //main menu
		break;

	case 1:	
		load.open("Levels/map1.dat");
		if (!load.is_open()) //close if map not found
		{
			window.close();
			musicPlayer.stop(music);
			MessageBox(0, "Unable to load map1.dat", "Error loading resource", MB_ICONERROR);
			exit(1);
		}

		for (unsigned int i = 0; i < LEVEL_HEIGHT * LEVEL_WIDTH; ++i)
		{
			load >> tileType;
			map[tileY][tileX] = tileType;

			++tileX;
			if (tileX > 24)
			{
				tileX = 0;
				++tileY;
			}
		}
		load.close();
		tiles.createMap(map);
		break;

	case 2:
		load.open("Levels/map2.dat");
		if (!load.is_open()) //close if map not found
		{
			window.close();
			musicPlayer.stop(music);
			MessageBox(0, "Unable to load map1.dat", "Error loading resource", MB_ICONERROR);
			exit(1);
		}

		for (unsigned int i = 0; i < LEVEL_HEIGHT * LEVEL_WIDTH; ++i)
		{
			load >> tileType;
			map[tileY][tileX] = tileType;

			++tileX;
			if (tileX > 24)
			{
				tileX = 0;
				++tileY;
			}
		}
		load.close();
		tiles.createMap(map);
		break;
	};
}

void Game::currentMusic()
{
	musicPlayer.play(levelState, startMusic, music);
}

int Game::mainMenu()
{
	noEnemyClock.restart(); //keep clock set to zero until game starts

	window.setView(menuView);
	window.clear();

	gameState = menu.getInput(window, event, menuSound, menuSelectSound);
	menu.render(window, backgroundS, menuTextS, optionTextS, font);

	if (gameState == 1)
	{
		reset();
		levelState = 1; //game started, set level to 1
		loadLevel(); //load first map
		startMusic = true;
		players.setPlayers();
	}
	else
		levelState = 0;

	window.display();

	return gameState;
}

int Game::optionMenu()
{
	window.setView(menuView);
	window.clear();

	gameState = menu.getInput(window, event, menuSound, menuSelectSound);
	menu.render(window, backgroundS, menuTextS, optionTextS, font);

	window.display();

	return gameState;
}

int Game::getDebug()
{
	return menu.getDebug();
}

void Game::showDebug(int fps)
{
	std::stringstream debugStream;
	debugStream << "FPS: " << fps << std::endl << "Position: " << view.getCenter().y;

	showFps.setFont(font);
	showFps.setColor(sf::Color::Black);
	showFps.setCharacterSize(25);
	showFps.setString(debugStream.str());
}

void Game::nextLevelReset()
{
	//clear all data
	for (unsigned int i = 0; i < playerBullets.size(); ++i)
		delete playerBullets.at(i);
	playerBullets.clear();

	for (unsigned int i = 0; i < enemyBullets.size(); ++i)
		delete enemyBullets.at(i);
	enemyBullets.clear();

	for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
		delete enemyPlanes.at(i);
	enemyPlanes.clear();

	if (boss1) //check if boss exists
	{
		boss1 = NULL;
		delete boss1;
	}

	players.nextLevelReset(); //reset player for next level

	lose = false;
	win = false;
	loseClock.restart();
	winClock.restart();

	currentMusic();
	startMusic = true;

	noEnemies = true;
	noEnemyTimer = sf::seconds(0); //reset enemy creation timer to 0

	createBoss = false;
	killedBoss = false;

	view.setCenter(500, VIEW_START_LOCATION);

	loadLevel();
}

void Game::reset()
{
	//clear all data
	for (unsigned int i = 0; i < playerBullets.size(); ++i)
		delete playerBullets.at(i);
	playerBullets.clear();

	for (unsigned int i = 0; i < enemyBullets.size(); ++i)
		delete enemyBullets.at(i);
	enemyBullets.clear();

	for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
		delete enemyPlanes.at(i);
	enemyPlanes.clear();

	if (boss1) //check if boss exists
	{
		boss1 = NULL;
		delete boss1;
	}

	if (boss2) //check if boss exists
	{
		boss2 = NULL;
		delete boss2;
	}

	players.reset();

	lose = false;
	win = false;
	completedGame = false;
	loseClock.restart();
	winClock.restart();

	currentMusic();
	startMusic = true;

	noEnemies = true;
	noEnemyTimer = sf::seconds(0); //reset enemy creation timer to 0

	createBoss = false;
	killedBoss = false;

	view.setCenter(500, VIEW_START_LOCATION);
	lockScreen = false;

	menu.setGameState(0);
	loadLevel();

	creditPos = 0;
}

void Game::spawnBoss()
{	
	if (levelState == 1)
	{
		bossTextTime = bossTextClock.getElapsedTime();
		bossAproaching.setPosition(view.getCenter().x - 100, view.getCenter().y - 100); //set bossAproaching text to center of screen

		if (view.getCenter().y <= 50000 && createBoss == false)
			createBoss = true;

		if (createBoss == true && killedBoss == false)
		if (!boss1) //if boss doesn't alreay exist, create it
		{
			bossTextClock.restart();
			boss1 = new Boss1(view.getCenter().x, view.getCenter().y - 1000, menu, alertSound);
		}
	}

	if (levelState == 2)
	{
		bossTextTime = bossTextClock.getElapsedTime();
		bossAproaching.setPosition(view.getCenter().x - 100, view.getCenter().y - 100); //set bossAproaching text to center of screen

		if (view.getCenter().y <= 43000 && createBoss == false)
			createBoss = true;

		if (createBoss == true && killedBoss == false)
		if (!boss2) //if boss doesn't alreay exist, create it
		{
			bossTextClock.restart();
			boss2 = new Boss2(view.getCenter().x, view.getCenter().y - 1000, menu, alertSound);
		}
	}

	if (boss2 && view.getCenter().y <= 42400)
		lockScreen = true;
}

void Game::killBoss()
{	
	if (boss1)
	{
		if (boss1->getDead() == true && boss1->getOffScreen(view) == true)
		{
			bossExpSound.play();
			killedBoss = true;
			boss1 = NULL;
			delete boss1;
			win = true;
		}
	}

	if (boss2)
	{
		if (boss2->getHealth() <= 0)
			lockScreen = false;

		if (boss2->getDead() == true && boss2->getOffScreen(view) == true)
		{
			bossExpSound.play();
			killedBoss = true;
			boss2 = NULL;
			delete boss2;
			win = true;
		}
	}
}

int Game::checkPlayerWinLose()
{
	int state = 1; //set state to in game

	//check win
	if (win)
	{
		completedGameTime = completedGameClock.getElapsedTime();

		winTime = winClock.getElapsedTime();
		mssionComplete.setPosition(view.getCenter().x - 450, view.getCenter().y - 200);

		//kill all enemy planes
		for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
		{
			enemyPlanes.at(i)->kill();
		}

		if (winTime.asSeconds() > 4)
		{
			if (levelState == 1)
			{
				levelState = 2; //next level
				nextLevelReset();
			}
			else if (levelState == 2)
			{
				levelState = 3;

				//stop sounds
				alertSound.stop();
				missileSound.stop();
				music.stop();

				completedGameClock.restart();
				completedGameTime = completedGameClock.getElapsedTime();	

				completedGame = true;
				if (completedGame)
				{
					endingMusic.openFromFile("Sound/ending.wav");
					endingMusic.play();
				}
			}
			else if (levelState == 3) //finished game, return to main menu
			{		
				window.setView(menuView);

				if (completedGameTime.asSeconds() >= 5 && (sf::Joystick::isButtonPressed(0, Start) || sf::Joystick::isButtonPressed(1, Start) || sf::Joystick::isButtonPressed(2, Start)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				{
					//reset states
					gameState = 0;
					levelState = 0;
					completedGame = false;

					//reset music
					endingMusic.stop();
					currentMusic();
					startMusic = true;

					state = 0; //change state back to main menu
				}
			}
		}
	}
	else
		winClock.restart();

	//check lose
	bool alive1 = false, alive2 = false, alive3 = false; //player alive states
	for (int i = 0; i < menu.getPlayers(); ++i)
	{
		if (players.getAlive(i) == true || players.getLives(i) > 0)
		{
			switch (i)
			{
			case 0:
				alive1 = true;
				break;

			case 1:
				alive2 = true;
				break;

			case 2:
				alive3 = true;
				break;
			};
		}

		//check if all players have died
		if (alive1 == false && alive2 == false && alive3 == false) 
			lose = true;	
		else
		{
			loseClock.restart();
			lose = false;
		}
	}

	if (lose)
	{
		loseTime = loseClock.getElapsedTime();
		gameOver.setPosition(view.getCenter().x - 340, view.getCenter().y - 190);

		if (loseTime.asSeconds() > 4)
		{
			state = 0;
			
			gameState = 0;
			levelState = 0;
			currentMusic();
			startMusic = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && completedGame == false)
	{
		//reset states
		gameState = 0;
		levelState = 0;

		//stop sounds
		alertSound.stop();
		missileSound.stop();

		//reset music
		currentMusic();
		startMusic = true;

		state = 0; //change state back to main menu
	}

	return state;
}

void Game::update()
{
	/*
	*prevent screen movement after game completed
	*necessary to prevent credits timing from being
	*interfered with
	*/
	if (!completedGame)
		while (window.pollEvent(event)); //event loop

	players.changeInvincible(); //set to not invincible after specified time
	createEnemies();
	spawnBoss();
	killBoss();
	players.useLife(); //restore player if dead and has remaining lives
	players.input(view); //get user input
	playerFireGun(); //fire player gun
	enemyFireGun(); //fire enemy gun
	itemPickup.destroyItem(view);

	//update bullet and missile position and delete
	{
		//player missiles
		for (unsigned int i = 0; i < playerMissiles.size(); ++i)
		{
			playerMissiles.at(i)->move();

			if (playerMissiles.at(i)->destroy(view) == true)
			{
				delete playerMissiles.at(i);
				playerMissiles.erase(playerMissiles.begin() + i);
			}
		}


		//player bullets
		for (unsigned int i = 0; i < playerBullets.size(); ++i)
		{
			sf::Vector2f enemyCoords; //current enemy coordinates
			bool bulletMoved = false; //check if bullet has already moved

			if (enemyPlanes.size() > 0)
			{
				int closestObject = 0; //current closest object identifier
				float closestObjectCoords = 0; //object coords

				for (unsigned int j = 0; j < enemyPlanes.size(); ++j)
				{
					/*
					*		-NOTE ONLY APPLIES TO HOMING GUN-
					*get distance of enemy object from player plane
					*if distance is the current least distance from player
					*set current object to that corresponding enemy
					*/
					switch (playerBullets.at(i)->getOwner())
					{
					case player1:
						if (getDistance(players.getPlayerPos(player1), enemyPlanes.at(j)->getCoords()) < closestObjectCoords || j == 0)
						{
							closestObjectCoords = getDistance(players.getPlayerPos(player1), enemyPlanes.at(j)->getCoords());
							closestObject = j;
						}
						break;

					case player2:
						if (getDistance(players.getPlayerPos(player2), enemyPlanes.at(j)->getCoords()) < closestObjectCoords || j == 0)
						{
							closestObjectCoords = getDistance(players.getPlayerPos(player2), enemyPlanes.at(j)->getCoords());
							closestObject = j;
						}
						break;

					case player3:
						if (getDistance(players.getPlayerPos(player3), enemyPlanes.at(j)->getCoords()) < closestObjectCoords || j == 0)
						{
							closestObjectCoords = getDistance(players.getPlayerPos(player3), enemyPlanes.at(j)->getCoords());
							closestObject = j;
						}
						break;
					};
				}
				enemyCoords = enemyPlanes.at(closestObject)->getCoords(); //set coordinates to closest enemy object

				/*
				*		-NOTE ONLY APPLIES TO HOMING GUN-
				*if boss exists, check if it is the closest enemy
				*object to current player bullet, if it is set new
				*bullet target to boss
				*/
				if (boss1)
				{
					switch (playerBullets.at(i)->getOwner())
					{
					case player1:
						if (cmpEnemyDToBossD(players.getPlayerPos(player1), enemyCoords, boss1->getCoords()) == true)
						{
							enemyCoords = boss1->getCoords();
							playerBullets.at(i)->move(sf::Vector2f(boss1->getCoords())); //move bullet
							bulletMoved = true;
						}
						break;

					case player2:
						if (cmpEnemyDToBossD(players.getPlayerPos(player2), enemyCoords, boss1->getCoords()) == true)
						{
							enemyCoords = boss1->getCoords();
							playerBullets.at(i)->move(sf::Vector2f(boss1->getCoords())); //move bullet
							bulletMoved = true;
						}
						break;

					case player3:
						if (cmpEnemyDToBossD(players.getPlayerPos(player3), enemyCoords, boss1->getCoords()) == true)
						{
							enemyCoords = boss1->getCoords();
							playerBullets.at(i)->move(sf::Vector2f(boss1->getCoords())); //move bullet
							bulletMoved = true;
						}
						break;
					};
				}
			}			
			else
				enemyCoords = sf::Vector2f(0, 0); //if no enemies exist homing gun functions as regular machine gun

			if (boss2)
				enemyCoords = sf::Vector2f(boss2->getCoords().x, boss2->getCoords().y + 300);

			if (!bulletMoved)
				playerBullets.at(i)->move(enemyCoords); //move bullet

			//if bullet has gone off screen destroy it
			if (playerBullets.at(i)->destroy(view) == true)
			{
				delete playerBullets.at(i);
				playerBullets.erase(playerBullets.begin() + i);
			}
		}


		//enemy bullets
		for (unsigned int i = 0; i < enemyBullets.size(); ++i)
		{
			enemyBullets.at(i)->move();

			if (enemyBullets.at(i)->destroy(view) == true)
			{
				if (enemyBullets.at(i) != NULL)
				{
					delete enemyBullets.at(i);
					enemyBullets.erase(enemyBullets.begin() + i);
				}
			}
		}
	}


	//destroy enemy plane objects that have died
	for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
	{
		bool planeDead = enemyPlanes.at(i)->getDead();
		if (planeDead == true)
		{
			if (enemyPlanes.at(i) != NULL)
			{
				delete enemyPlanes.at(i);
				enemyPlanes.erase(enemyPlanes.begin() + i);
			}
		}
	}

	//update enemy planes
	for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
		enemyPlanes.at(i)->move(view); //update movement

	//if boss exists, update boss
	if (boss1)
		boss1->move(view, players);
	
	checkCollisions();
}

void Game::updateGraphics()
{
	//if finished game display ending screen
	if (completedGame)
	{
		std::stringstream playerScores;
		playerScores << "\nPlayer 1 " << players.getScore(player1) << "\n\nPlayer 2 "
			<< players.getScore(player2) << "\n\nPlayer 3 " << players.getScore(player3);
		winEasy.setString("\t\t\tCongradulations!\nYou have completed Sky Fighter\n\t\ton easy difficulty.\n"
			"Next time try hard difficulty.\n\n" + playerScores.str());
		winHard.setString("\t\t\tCongradulations!\nYou have completed Sky Fighter\n\t\ton hard difficulty.\n"
			"You have completed the ultimate\n challenge in Sky Fighter!\n\n" + playerScores.str());

		window.clear();
		winScreenS.setScale(1.3f, 1.4f);
		winScreenS.setPosition(-650, -500);

		window.draw(winScreenS);

		if (menu.getDifficulty() == 0)
		{
			winEasy.setPosition(sf::Vector2f(menuView.getCenter().x - 450, menuView.getCenter().y + 400 + creditPos));
			window.draw(winEasy);
		}
		else if (menu.getDifficulty() == 1)
		{
			winHard.setPosition(sf::Vector2f(menuView.getCenter().x - 450, menuView.getCenter().y + 400 + creditPos));
			window.draw(winHard);
		}

		creditsEnding.setPosition(menuView.getCenter().x - 400, menuView.getCenter().y + 1200 + creditPos);
		window.draw(creditsEnding);

		if (creditPos > -4250)
			creditPos -= .804f;
		else
		{
			pushStart.setPosition(menuView.getCenter().x - 200, menuView.getCenter().y + 300);
			int flashStart = (int)completedGameTime.asSeconds();

			if (flashStart % 2 == 0)
				window.draw(pushStart);
		}
	}
	else
	{
		window.clear(); //clear screen

		window.draw(tiles.getMapVA(), &tileT); //render tilemap

		itemPickup.render(window, itemS);

		//render all players and enemies
		{
			//if boss exists, render
			if (boss2)
				boss2->render(window, boss2S, expS);

			//render players
			players.render(window, planeS, expS);

			//if boss exists, render
			if (boss1)
				boss1->render(window, boss1S, expS);

			//render enemy planes
			for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
				enemyPlanes.at(i)->render(window, planeS, expS);
		}

		//render bullets and missiles
		{
			//player missiles
			for (unsigned int i = 0; i < playerMissiles.size(); ++i)
				playerMissiles.at(i)->render(window, smokeS, missileS);

			//player bullets
			for (unsigned int i = 0; i < playerBullets.size(); ++i)
				playerBullets.at(i)->render(window);

			//enemy bullets
			for (unsigned int i = 0; i < enemyBullets.size(); ++i)
				enemyBullets.at(i)->render(window);
		}

		particle.update(window); //update particle effects

		players.HUD(window, view, hudS, font); //head up display

		//debug info
		{
			showFps.setPosition(view.getCenter().x - 500, view.getCenter().y - 500);
			window.draw(showFps);
		}

		int flashBossText = (int)bossTextTime.asSeconds();
		if (win)
			window.draw(mssionComplete); //display win message
		else if (lose)
			window.draw(gameOver); //display "Game over" if lost
		else if ((boss1 || boss2) && bossTextTime.asSeconds() < 5 && flashBossText % 2 == 0) //display boss approaching text if boss was just created
			window.draw(bossAproaching);

		moveScreen(); //move screen view forward
	}

	window.display(); //update screen
	window.setVerticalSyncEnabled(true);
}

void Game::moveScreen()
{
	if (!lockScreen) //move unless screen is locked
	{
		//move screen forward by const MOVE_SPEED
		view.move(0, MOVE_SPEED);
		window.setView(view);

		players.lockScreenPos(false); //unlock player position
	}
	else if (lockScreen) //lock position
		players.lockScreenPos(true);
}

void Game::playerFireGun()
{
	if (levelState != 3)
	{
		enum bulletTypes{ machineGun, homing, dualGun };
		gunTime = gunClock.getElapsedTime();
		gunSoundTime = gunSoundClock.getElapsedTime();

		bool missile1, missile2, missile3;
		bool fire1, fire2, fire3;
		float x1, y1, x2, y2, x3, y3;
		players.getFiring(fire1, fire2, fire3, missile1, missile2, missile3); //get firing states

		//gun sound
		if (((fire1 == true && players.getEquippedGunType(player1) != dualGun) || (fire2 == true && players.getEquippedGunType(player2) != dualGun)
			|| (fire3 == true && players.getEquippedGunType(player1) != dualGun)) && gunSoundTime.asMilliseconds() > GUN_SOUND_RATE)
		{
			gunSound.play();
			gunSoundClock.restart();
		}

		if (((fire1 == true && players.getEquippedGunType(player1) == dualGun) || (fire2 == true && players.getEquippedGunType(player2) == dualGun)
			|| (fire3 == true && players.getEquippedGunType(player3) == dualGun)) && gunSoundTime.asMilliseconds() > GUN_SOUND_RATE)
		{
			heavyGunSound.play();
			gunSoundClock.restart();
		}

		//missile sound
		if (missile1 == true || missile2 == true || missile3 == true)
			missileSound.play();

		if (fire1 == true && gunTime.asMilliseconds() > FIRE_RATE)
		{
			if (players.getEquippedGunType(player1) != dualGun) //if not gun type dual gun(2)
			{
				//create bullets at location of player1
				players.getXY(x1, y1, x2, y2, x3, y3);
				PlayerBullet* bullet = new PlayerBullet(x1, y1, player1, players.getEquippedGunType(player1));
				playerBullets.push_back(bullet);
			}
			else
			{
				//create bullets at location of player1
				players.getXY(x1, y1, x2, y2, x3, y3);

				for (int i = 0; i < 2; ++i)
				{
					PlayerBullet* bullet = new PlayerBullet((x1 - 20) + i * 30, y1, player1, players.getEquippedGunType(player1));
					playerBullets.push_back(bullet);
				}
			}
		}
		if (fire2 == true && gunTime.asMilliseconds() > FIRE_RATE)
		{
			if (players.getEquippedGunType(player2) != dualGun) //if not gun type dual gun(2)
			{
				//create bullets at location of player2
				players.getXY(x1, y1, x2, y2, x3, y3);
				PlayerBullet* bullet = new PlayerBullet(x2, y2, player2, players.getEquippedGunType(player2));
				playerBullets.push_back(bullet);
			}
			else
			{
				//create bullets at location of player1
				players.getXY(x1, y1, x2, y2, x3, y3);

				for (int i = 0; i < 2; ++i)
				{
					PlayerBullet* bullet = new PlayerBullet((x2 - 20) + i * 30, y2, player2, players.getEquippedGunType(player2));
					playerBullets.push_back(bullet);
				}
			}
		}
		if (fire3 == true && gunTime.asMilliseconds() > FIRE_RATE)
		{
			if (players.getEquippedGunType(player2) != dualGun) //if not gun type dual gun(2)
			{
				//create bullets at location of player3
				players.getXY(x1, y1, x2, y2, x3, y3);
				PlayerBullet* bullet = new PlayerBullet(x3, y3, player3, players.getEquippedGunType(player3));
				playerBullets.push_back(bullet);
			}
			else
			{
				//create bullets at location of player1
				players.getXY(x1, y1, x2, y2, x3, y3);

				for (int i = 0; i < 2; ++i)
				{
					PlayerBullet* bullet = new PlayerBullet((x3 - 20) + i * 30, y3, player3, players.getEquippedGunType(player3));
					playerBullets.push_back(bullet);
				}
			}
		}

		if (gunTime.asMilliseconds() > FIRE_RATE)
			gunClock.restart();

		//create missiles
		if (missile1 == true)
		{
			players.getXY(x1, y1, x2, y2, x3, y3);
			PlayerMissile* missile = new PlayerMissile(x1 + 65, y1 - 10, player1);
			playerMissiles.push_back(missile);
		}
		if (missile2 == true)
		{
			players.getXY(x1, y1, x2, y2, x3, y3);
			PlayerMissile* missile = new PlayerMissile(x2 + 65, y2 - 10, player2);
			playerMissiles.push_back(missile);
		}
		if (missile3 == true)
		{
			players.getXY(x1, y1, x2, y2, x3, y3);
			PlayerMissile* missile = new PlayerMissile(x3 + 65, y3 - 10, player3);
			playerMissiles.push_back(missile);
		}
	}
}

void Game::enemyFireGun()
{
	for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
	{
		if (enemyPlanes.at(i)->fireGun() == true)
		{
			sf::Vector2f enemyPlaneCoords;
			enemyPlaneCoords = enemyPlanes.at(i)->getCoords();

			EnemyBullet* enemyBullet = new EnemyBullet(enemyPlaneCoords.x, enemyPlaneCoords.y);
			enemyBullets.push_back(enemyBullet);
		}
	}

	if (boss1)
	{
		if (boss1->fireGun() == true)
		{
			sf::Vector2f bossPlaneCoords;
			bossPlaneCoords = boss1->getCoords();

			for (int i = 0; i < 4; ++i)
			{
				if (i == 0)
				{
					EnemyBullet* enemyBullet = new EnemyBullet(bossPlaneCoords.x - 70, bossPlaneCoords.y + 43);
					enemyBullets.push_back(enemyBullet);
				}

				if (i == 1)
				{
					EnemyBullet* enemyBullet = new EnemyBullet(bossPlaneCoords.x - 50, bossPlaneCoords.y + 43);
					enemyBullets.push_back(enemyBullet);
				}

				if (i == 2)
				{
					EnemyBullet* enemyBullet = new EnemyBullet(bossPlaneCoords.x + 10, bossPlaneCoords.y + 43);
					enemyBullets.push_back(enemyBullet);
				}

				if (i == 3)
				{
					EnemyBullet* enemyBullet = new EnemyBullet(bossPlaneCoords.x + 27, bossPlaneCoords.y + 43);
					enemyBullets.push_back(enemyBullet);
				}
			}
		}
	}
	if (boss2)
	{
		//turret gun
		if (boss2->getGunTime().asMilliseconds() < 500 && boss2->getGunTime().asMilliseconds() % 3 == 0)
		{
			for (int i = 0; i < 2; ++i)
			{

				EnemyBullet* enemyBullet = new EnemyBullet((boss2->getCoords().x - 16 + i * 15), boss2->getCoords().y + 200);
				enemyBullets.push_back(enemyBullet);
			}
		}

		//circular gun
		if (boss2->fireGun() == true) 
		{
			if (enemyPlanes.size() > 0)
			{
				for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
				{
					enemyPlanes.at(i)->kill();
				}
			}

			sf::Vector2f gunCoords = boss2->getCoords();
			gunCoords.x -= 50;
			gunCoords.y += 400;
			for (int i = 0; i < TOTAL_BULLETS_FIRED; ++i)
			{
				//create circular bullet pattern
				EnemyBullet* enemyBullet = new EnemyBullet(gunCoords);
				enemyBullets.push_back(enemyBullet);
			}
		}
	}
}

void Game::checkCollisions()
{
	enum bulletTypes{ machineGun, homing, dualGun };
	hitSoundTime = hitSoundClock.getElapsedTime();

	itemPickup.pickup(players, itemPickupSound); //item collisions

	//bullet collisions
	{
		//bullet collisions with enemies
		for (unsigned int i = 0; i < playerBullets.size(); ++i)
		{
			//boss
			if (boss1)
			{
				if (collision(playerBullets.at(i)->bulletBox.getPosition(), playerBullets.at(i)->bulletBox.getSize(),
					boss1->enemyBox.getPosition(), boss1->enemyBox.getSize()) == true)
				{
					//play hit1 sound at limited rate
					if (hitSoundTime.asMilliseconds() > HIT_SOUND_RATE && boss1->getAlive() == true)
					{
						hitSound1.play();
						hitSoundClock.restart();
					}

					//do damange on enemy at gun type damage rate
					if (playerBullets.at(i)->getType() == machineGun)
						boss1->subHealth(MACHINE_GUN_DAMAGE);
					else if (playerBullets.at(i)->getType() == homing)
						boss1->subHealth(HOMING_GUN_DAMAGE);
					else if (playerBullets.at(i)->getType() == dualGun)
						boss1->subHealth(DUAL_GUN_DAMAGE);

					if (boss1->getHealth() <= 0)
					{
						//play explosion sound
						if (boss1->getAlive() == true)
						{
							explodeSound.play();
							players.setScore(playerBullets.at(i)->getOwner(), 500, lifeUpSound); //pass in owner of bullet to setScore to add points to players total score
						}
						boss1->kill(); //kill enemy plane	
					}

					//destroy bullets that hit plane
					delete playerBullets.at(i);
					playerBullets.erase(playerBullets.begin() + i);
					break;
				}
			}
			else if (boss2)
			{
				if (collision(playerBullets.at(i)->bulletBox.getPosition(), playerBullets.at(i)->bulletBox.getSize(),
					boss2->enemyBox.getPosition(), boss2->enemyBox.getSize()) == true)
				{
					//play hit1 sound at limited rate
					if (hitSoundTime.asMilliseconds() > HIT_SOUND_RATE && boss2->getAlive() == true)
					{
						hitSound1.play();
						hitSoundClock.restart();
					}

					//do damange on enemy at gun type damage rate
					if (playerBullets.at(i)->getType() == machineGun)
						boss2->subHealth(MACHINE_GUN_DAMAGE);
					else if (playerBullets.at(i)->getType() == homing)
						boss2->subHealth(HOMING_GUN_DAMAGE);
					else if (playerBullets.at(i)->getType() == dualGun)
						boss2->subHealth(DUAL_GUN_DAMAGE);

					if (boss2->getHealth() <= 0)
					{
						//play explosion sound
						if (boss2->getAlive() == true)
						{
							explodeSound.play();
							players.setScore(playerBullets.at(i)->getOwner(), 500, lifeUpSound); //pass in owner of bullet to setScore to add points to players total score
						}
						boss2->kill(); //kill enemy plane	
					}

					//destroy bullets that hit plane
					delete playerBullets.at(i);
					playerBullets.erase(playerBullets.begin() + i);
					break;
				}
			}

			//planes
			for (unsigned int j = 0; j < enemyPlanes.size(); ++j)
			{
				if (collision(playerBullets.at(i)->bulletBox.getPosition(), playerBullets.at(i)->bulletBox.getSize(),
					enemyPlanes.at(j)->enemyBox.getPosition(), enemyPlanes.at(j)->enemyBox.getSize()) == true)
				{
					//play hit1 sound at limited rate
					if (hitSoundTime.asMilliseconds() > HIT_SOUND_RATE && enemyPlanes.at(j)->getAlive() == true)
					{
						hitSound1.play();
						hitSoundClock.restart();
					}

					//do damange on enemy at gun type damage rate
					if (playerBullets.at(i)->getType() == machineGun)
						enemyPlanes.at(j)->subHealth(MACHINE_GUN_DAMAGE);
					else if (playerBullets.at(i)->getType() == homing)
						enemyPlanes.at(j)->subHealth(HOMING_GUN_DAMAGE);
					else if (playerBullets.at(i)->getType() == dualGun)
						enemyPlanes.at(j)->subHealth(DUAL_GUN_DAMAGE);

					if (enemyPlanes.at(j)->getHealth() <= 0)
					{
						//play explosion sound
						if (enemyPlanes.at(j)->getAlive() == true)
						{
							itemPickup.createItem(playerBullets.at(i)->getPos());
							particle.createMediumExplosion(playerBullets.at(i)->getPos());
							explodeSound.play();

							players.setScore(playerBullets.at(i)->getOwner(), enemyPlanes.at(j)->getScoreAmount(), lifeUpSound); //pass in owner of bullet to setScore to add points to players total score
						}
						enemyPlanes.at(j)->kill(); //kill enemy plane				
					}

					//destroy bullets that hit plane
					delete playerBullets.at(i);
					playerBullets.erase(playerBullets.begin() + i);
					break;
				}
			}
		}

		//missile collisions with enemies
		for (unsigned int i = 0; i < playerMissiles.size(); ++i)
		{
			//boss
			if (boss1)
			{
				if (collision(playerMissiles.at(i)->missileBox.getPosition(), playerMissiles.at(i)->missileBox.getSize(),
					boss1->enemyBox.getPosition(), boss1->enemyBox.getSize()) == true)
				{
					boss1->subHealth(MISSILE_DAMAGE);
					missileExplodeSound.play();

					if (boss1->getHealth() <= 0)
					{
						//play explosion sound
						if (boss1->getAlive() == true)
							explodeSound.play();
						
						boss1->kill(); //kill enemy plane
						players.setScore(playerMissiles.at(i)->getOwner(), 500, lifeUpSound); //pass in owner of missile to setScore to add points to players total score
					}

					delete playerMissiles.at(i);
					playerMissiles.erase(playerMissiles.begin() + i);
					break;
				}
			}
			else if (boss2)
			{
				if (collision(playerMissiles.at(i)->missileBox.getPosition(), playerMissiles.at(i)->missileBox.getSize(),
					boss2->enemyBox.getPosition(), boss2->enemyBox.getSize()) == true)
				{
					boss2->subHealth(MISSILE_DAMAGE);
					missileExplodeSound.play();

					if (boss2->getHealth() <= 0)
					{
						//play explosion sound
						if (boss2->getAlive() == true)
							explodeSound.play();

						boss2->kill(); //kill enemy plane
						players.setScore(playerMissiles.at(i)->getOwner(), 500, lifeUpSound); //pass in owner of missile to setScore to add points to players total score
					}

					delete playerMissiles.at(i);
					playerMissiles.erase(playerMissiles.begin() + i);
					break;
				}
			}

			//planes
			for (unsigned int j = 0; j < enemyPlanes.size(); ++j)
				if (collision(playerMissiles.at(i)->missileBox.getPosition(), playerMissiles.at(i)->missileBox.getSize(),
					enemyPlanes.at(j)->enemyBox.getPosition(), enemyPlanes.at(j)->enemyBox.getSize()) == true)
				{
					enemyPlanes.at(j)->subHealth(MISSILE_DAMAGE);
					missileExplodeSound.play();

					if (enemyPlanes.at(j)->getHealth() <= 0)
					{
						//play explosion sound
						if (enemyPlanes.at(j)->getAlive() == true)
						{
							itemPickup.createItem(enemyPlanes.at(i)->getCoords());
							particle.createMediumExplosion(playerMissiles.at(i)->getPos());
							explodeSound.play();
						}

						enemyPlanes.at(j)->kill(); //kill enemy plane
						players.setScore(playerMissiles.at(i)->getOwner(), enemyPlanes.at(j)->getScoreAmount(), lifeUpSound); //pass in owner of missile to setScore to add points to players total score
					}

					delete playerMissiles.at(i);
					playerMissiles.erase(playerMissiles.begin() + i);
					break;
				}
		}

		//bullet collisions with player planes
		for (unsigned int i = 0; i < enemyBullets.size(); ++i)
		{
			//player 1
			if (collision(players.playerBox1.getPosition(), players.playerBox1.getSize(), enemyBullets.at(i)->bulletBox.getPosition(), enemyBullets.at(i)->bulletBox.getSize()) == true
				&& players.getInvincible(player1) == false && players.getAlive(player1) == true)
			{
				particle.createSmallExplosion(enemyBullets.at(i)->getPos());
				hitSound.play();

				players.subHealth(ENEMY_GUN_DAMAGE, player1); //subtract player health

				if (players.getHealth(player1) <= 0) //if dead
				{
					particle.createMediumExplosion(enemyBullets.at(i)->getPos());
					dieExplodeSound.play();
					players.kill(player1);
				}

				delete enemyBullets.at(i);
				enemyBullets.erase(enemyBullets.begin() + i);
				continue; //end instance of current collision
			}
			//player 2
			if (menu.getPlayers() > 1)
			if (collision(players.playerBox2.getPosition(), players.playerBox2.getSize(), enemyBullets.at(i)->bulletBox.getPosition(), enemyBullets.at(i)->bulletBox.getSize()) == true
				&& players.getInvincible(player2) == false && players.getAlive(player2) == true)
			{
				particle.createSmallExplosion(enemyBullets.at(i)->getPos());
				hitSound.play();

				players.subHealth(ENEMY_GUN_DAMAGE, player2); //subtract player health

				if (players.getHealth(player2) <= 0) //if dead
				{
					particle.createMediumExplosion(enemyBullets.at(i)->getPos());
					dieExplodeSound.play();
					players.kill(player2);
				}

				delete enemyBullets.at(i);
				enemyBullets.erase(enemyBullets.begin() + i);
				continue; //end instance of current collision
			}
			//player 3
			if (menu.getPlayers() > 2)
			if (collision(players.playerBox3.getPosition(), players.playerBox3.getSize(), enemyBullets.at(i)->bulletBox.getPosition(), enemyBullets.at(i)->bulletBox.getSize()) == true
				&& players.getInvincible(player3) == false && players.getAlive(player3) == true)
			{
				particle.createSmallExplosion(enemyBullets.at(i)->getPos());
				hitSound.play();

				players.subHealth(ENEMY_GUN_DAMAGE, player3); //subtract player health

				if (players.getHealth(player3) <= 0) //if dead
				{
					particle.createMediumExplosion(enemyBullets.at(i)->getPos());
					dieExplodeSound.play();
					players.kill(player3);
				}

				delete enemyBullets.at(i);
				enemyBullets.erase(enemyBullets.begin() + i);
			}
		}
	}

	//player collides with enemies

	//boss
	if (boss1)
	{
		if (collision(boss1->enemyBox.getPosition(), boss1->enemyBox.getSize(),
			players.playerBox1.getPosition(), players.playerBox1.getSize()) == true && (boss1->getAlive() == true) && players.getInvincible(player1) == false)
		{
			particle.createMediumExplosion(players.getPlayerPos(player1));
			dieExplodeSound.play();
			players.kill(player1); //kill current player
		}

		if (collision(boss1->enemyBox.getPosition(), boss1->enemyBox.getSize(),
			players.playerBox2.getPosition(), players.playerBox2.getSize()) == true && (boss1->getAlive() == true) && players.getInvincible(player2) == false)
		{
			particle.createMediumExplosion(players.getPlayerPos(player2));
			dieExplodeSound.play();
			players.kill(player2); //kill current player
		}

		if (collision(boss1->enemyBox.getPosition(), boss1->enemyBox.getSize(),
			players.playerBox3.getPosition(), players.playerBox3.getSize()) == true && (boss1->getAlive() == true) && players.getInvincible(player3) == false)
		{
			particle.createMediumExplosion(players.getPlayerPos(player3));
			dieExplodeSound.play();
			players.kill(player3); //kill current player
		}
	}

	//planes
	for (unsigned int i = 0; i < enemyPlanes.size(); ++i)
	{
		if (players.getAlive(player1) == true) //prevent collisions with dead players
		{
			//player 1
			if (collision(enemyPlanes.at(i)->enemyBox.getPosition(), enemyPlanes.at(i)->enemyBox.getSize(),
				players.playerBox1.getPosition(), players.playerBox1.getSize()) == true && (enemyPlanes.at(i)->getAlive() == true) && players.getInvincible(player1) == false)
			{
				particle.createMediumExplosion(players.getPlayerPos(player1));
				dieExplodeSound.play();
				enemyPlanes.at(i)->kill(); //kill enemy plane
				players.kill(player1); //kill current player
				
			}
		}
		if (players.getAlive(player2) == true && menu.getPlayers() > 1) //prevent collisions with dead players
		{
			//player 2
			if (collision(enemyPlanes.at(i)->enemyBox.getPosition(), enemyPlanes.at(i)->enemyBox.getSize(),
				players.playerBox2.getPosition(), players.playerBox2.getSize()) == true && (enemyPlanes.at(i)->getAlive() == true) && players.getInvincible(player2) == false)
			{
				particle.createMediumExplosion(players.getPlayerPos(player2));
				dieExplodeSound.play();
				enemyPlanes.at(i)->kill(); //kill enemy plane
				players.kill(player2); //kill current player
			}
		}
		if (players.getAlive(player3) == true && menu.getPlayers() > 2) //prevent collisions with dead players
		{
			//player 3
			if (collision(enemyPlanes.at(i)->enemyBox.getPosition(), enemyPlanes.at(i)->enemyBox.getSize(),
				players.playerBox3.getPosition(), players.playerBox3.getSize()) == true && (enemyPlanes.at(i)->getAlive() == true) && players.getInvincible(player3) == false)
			{
				particle.createMediumExplosion(players.getPlayerPos(player3));
				dieExplodeSound.play();
				enemyPlanes.at(i)->kill(); //kill enemy plane
				players.kill(player3); //kill current player		
			}
		}
	}
}

void Game::createEnemies()
{
	newEnemyPlanetime = newEnemyPlaneclock.getElapsedTime();

	//get elapsed time for timer
	if (gameState == 1 && noEnemies == true)
		noEnemyTimer = noEnemyClock.getElapsedTime();
	
	//if over specified time allow enemies to be created
	if (noEnemyTimer.asSeconds() >= 2)
		noEnemies = false;

	//create enemy planes
	if (newEnemyPlanetime.asSeconds() > 1 && noEnemies == false && enemyPlanes.size() <= MAX_ON_SCREEN_ENEMIES && win == false)
	{
		//if reached near end of level 1 create max planes * 2
		if (view.getCenter().y <= 20000 && levelState == 1)
		{
			if (enemyPlanes.size() < MAX_ON_SCREEN_ENEMIES * 2)
			{
				EnemyPlanes* enemyPlane = new EnemyPlanes(view, menu);
				enemyPlanes.push_back(enemyPlane);
			}
		}
		else if ((menu.getDifficulty() == 1 && newEnemyPlanetime.asSeconds() > ENEMY_CREATE_RATE_HARD && !boss2) || 
			(menu.getDifficulty() == 0 && newEnemyPlanetime.asSeconds() > ENEMY_CREATE_RATE_EASY) && !boss2) //change enemy spawn rate based on difficulty level, don't create when boss2 is active
		{
			EnemyPlanes* enemyPlane = new EnemyPlanes(view, menu);
			enemyPlanes.push_back(enemyPlane);

			newEnemyPlaneclock.restart();
		}
	}
}