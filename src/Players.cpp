#include "Players.h"

sf::Clock Players::invincibleClock1;
sf::Clock Players::invincibleClock2;
sf::Clock Players::invincibleClock3;

Players::Players()
{
	//set starting player coords
	x1 = 100;
	y1 = PLAYER_START_LOCATION;
	x2 = 500;
	y2 = PLAYER_START_LOCATION;
	x3 = 800;
	y3 = PLAYER_START_LOCATION;

	//set default player velocities
	x1Vel = 0;
	y1Vel = 0;
	x2Vel = 0;
	y2Vel = 0;
	x3Vel = 0;
	y3Vel = 0;

	//player alive
	alive1 = true;
	alive2 = true;
	alive3 = true;

	//player dead
	dead1 = false;
	dead2 = false;
	dead3 = false;

	//set invincible
	invincible1 = false;
	invincible2 = false;
	invincible3 = false;
	flashInvincible = 0;

	//set player lives
	lives1 = PLAYER_STARTING_LIVES;
	lives2 = PLAYER_STARTING_LIVES;
	lives3 = PLAYER_STARTING_LIVES;

	//set player health
	health1 = PLAYER_HEALTH;
	health2 = PLAYER_HEALTH;
	health3 = PLAYER_HEALTH;

	//bounding boxes
	playerBox1.setSize(sf::Vector2f(65, 115));
	playerBox1.setPosition(this->x1, this->y1);

	playerBox2.setSize(sf::Vector2f(65, 115));
	playerBox2.setPosition(this->x2, this->y2);

	playerBox3.setSize(sf::Vector2f(65, 115));
	playerBox3.setPosition(this->x3, this->y3);

	//set explosion frame to 0
	explodeFrameX = 0;
	explodeFrameY = 0;

	//set score
	score1 = 0;
	score2 = 0;
	score3 = 0;
	showScore1 = 0;
	showScore2 = 0;
	showScore3 = 0;

	//gun overheat
	overheat1 = 0;
	overheat2 = 0;
	overheat3 = 0;
	overheated1 = false;
	overheated2 = false;
	overheated3 = false;

	//set gun type
	gunType1 = machineGun;
	gunType2 = machineGun;
	gunType3 = machineGun;

	//starting missiles and set missile cool down time off
	numMissile1 = STARTING_MISSILES;
	numMissile2 = STARTING_MISSILES;
	numMissile3 = STARTING_MISSILES;
	bonusMissile1 = 0;
	bonusMissile2 = 0;
	bonusMissile3 = 0;
	coolDownTime1 = sf::seconds(6);
	coolDownTime2 = sf::seconds(6);
	coolDownTime3 = sf::seconds(6);

	//set upgrade bullet count to 0
	bulletCount1 = 0;
	bulletCount2 = 0;
	bulletCount3 = 0;

	lockScreen = false; //lock player to screen position
}

void Players::input(sf::View& view)
{
	sf::Joystick::update();
	/*
	*keeps starting time set to 5 so missiles can be fired
	*at begining of game
	*/
	if (numMissile1 < STARTING_MISSILES + bonusMissile1)
		coolDownTime1 = coolDownClock1.getElapsedTime();
	if (numMissile2 < STARTING_MISSILES + bonusMissile2)
		coolDownTime2 = coolDownClock2.getElapsedTime();
	if (numMissile3 < STARTING_MISSILES + bonusMissile3)
		coolDownTime3 = coolDownClock3.getElapsedTime();

	//player input
	{
		if (alive1 == true)
		{
			float joyX1, joyY1;
			joyX1 = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			joyY1 = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			
			if (joyY1 == joyUp || sf::Keyboard::isKeyPressed(sf::Keyboard::W) && view.getCenter().y - y1 < MAX_TOP_PIXELS - 5)
				y1Vel = -PLAYER_Y_VEL + MOVE_SPEED;
			else if (joyY1 == joyDown || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y1 - view.getCenter().y < MAX_BOTTOM_PIXELS - 15)
				y1Vel = PLAYER_Y_VEL;
			else
			{
				if (lockScreen)
					y1Vel = 0;
				else
					y1Vel = MOVE_SPEED;
			}

			if (joyX1 == joyRight || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x1 - view.getCenter().x < MAX_RIGHT_PIXELS - 5)
				x1Vel = PLAYER_X_VEL;
			else if (joyX1 == joyLeft || sf::Keyboard::isKeyPressed(sf::Keyboard::A) && view.getCenter().x - x1 < MAX_LEFT_PIXELS)
				x1Vel = -PLAYER_X_VEL;
			else
				x1Vel = 0;

			//player 1 fire
			if (sf::Joystick::isButtonPressed(0, Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				fire1 = true;
			else
				fire1 = false;


			//player firing missile
			if ((sf::Joystick::isButtonPressed(0, A) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && coolDownTime1.asSeconds() > MISSILE_FIRE_RATE && (numMissile1 + bonusMissile1) > 0)
			{
				--numMissile1;
				missile1 = true;
				coolDownClock1.restart();
			}
			else
				missile1 = false;

			//keep player 1 on screen
			if (lockScreen && view.getCenter().y - y1 > MAX_TOP_PIXELS) //if screen is locked move player back if hits top
				y1Vel = 4;
			else if (view.getCenter().y - y1 > MAX_TOP_PIXELS) //keep player from going -y direction
				y1Vel = 0;
			if (y1 - view.getCenter().y > MAX_BOTTOM_PIXELS) //keep player from going +y direction
				y1Vel = MOVE_SPEED + MOVE_OUT_OFF_SCREEN;
			if (x1 - view.getCenter().x > MAX_RIGHT_PIXELS) //keep player from going +x direction
				x1Vel = -PLAYER_X_VEL;
			if (view.getCenter().x - x1 > MAX_LEFT_PIXELS) //keep player from going -x direction
				x1Vel = PLAYER_X_VEL;
		}

		if (alive2 == true)
		{
			float joyX2, joyY2;
			joyX2 = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
			joyY2 = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);

			if (joyY2 == joyUp && view.getCenter().y - y2 < MAX_TOP_PIXELS - 5)
				y2Vel = -PLAYER_Y_VEL + MOVE_SPEED;
			else if (joyY2 == joyDown && y2 - view.getCenter().y < MAX_BOTTOM_PIXELS - 15)
				y2Vel = PLAYER_Y_VEL;
			else
			{
				if (lockScreen)
					y2Vel = 0;
				else
					y2Vel = MOVE_SPEED;
			}

			if (joyX2 == joyRight && x2 - view.getCenter().x < 420 && x2 - view.getCenter().x < MAX_RIGHT_PIXELS - 5)
				x2Vel = PLAYER_X_VEL;
			else if (joyX2 == joyLeft && view.getCenter().x - x2 < 480 && view.getCenter().x - x2 < MAX_LEFT_PIXELS)
				x2Vel = -PLAYER_X_VEL;
			else
				x2Vel = 0;

			//player 2 fire
			if (sf::Joystick::isButtonPressed(1, Z))
				fire2 = true;
			else
				fire2 = false;


			//player firing missile
			if (sf::Joystick::isButtonPressed(1, A) && coolDownTime2.asSeconds() > MISSILE_FIRE_RATE && (numMissile2 + bonusMissile2) > 0)
			{
				--numMissile2;
				missile2 = true;
				coolDownClock2.restart();
			}
			else
				missile2 = false;

			//keep player 2 on screen
			if (lockScreen && view.getCenter().y - y2 > MAX_TOP_PIXELS) //if screen is locked move player back if hits top
				y2Vel = 4;
			else if (view.getCenter().y - y2 > MAX_TOP_PIXELS) //keep player from going -y direction
				y2Vel = 0;
			if (y2 - view.getCenter().y > MAX_BOTTOM_PIXELS) //keep player from going +y direction
				y2Vel = MOVE_SPEED + MOVE_OUT_OFF_SCREEN;
			if (x2 - view.getCenter().x > MAX_RIGHT_PIXELS) //keep player from going +x direction
				x2Vel = -PLAYER_X_VEL;
			if (view.getCenter().x - x2 > MAX_LEFT_PIXELS) //keep player from going -x direction
				x2Vel = PLAYER_X_VEL;
		}

		if (alive3 == true)
		{
			float joyX3, joyY3;
			joyX3 = sf::Joystick::getAxisPosition(2, sf::Joystick::X);
			joyY3 = sf::Joystick::getAxisPosition(2, sf::Joystick::Y);

			//player 3 movement
			if (joyY3 == joyUp && view.getCenter().y - y3 < MAX_TOP_PIXELS - 5)
				y3Vel = -PLAYER_Y_VEL + MOVE_SPEED;
			else if (joyY3 == joyDown && y3 - view.getCenter().y < MAX_BOTTOM_PIXELS - 15)
				y3Vel = PLAYER_Y_VEL;
			else
			{
				if (lockScreen)
					y3Vel = 0;
				else
					y3Vel = MOVE_SPEED;
			}
			if (joyX3 == joyRight && x2 - view.getCenter().x < 420 && x3 - view.getCenter().x < MAX_RIGHT_PIXELS - 5)
				x3Vel = PLAYER_X_VEL;
			else if (joyX3 == joyLeft && view.getCenter().x - x1 < 480 && view.getCenter().x - x3 < MAX_LEFT_PIXELS)
				x3Vel = -PLAYER_X_VEL;
			else
				x3Vel = 0;

			//player 3 fire
			if (sf::Joystick::isButtonPressed(2, Z))
				fire3 = true;
			else
				fire3 = false;

			//player firing missile
			if ((sf::Joystick::isButtonPressed(2, A)) && coolDownTime3.asSeconds() > MISSILE_FIRE_RATE && (numMissile3 + bonusMissile3) > 0)
			{
				--numMissile3;
				missile3 = true;
				coolDownClock3.restart();
			}
			else
				missile3 = false;

			//keep player 3 on screen
			if (lockScreen && view.getCenter().y - y3 > MAX_TOP_PIXELS) //if screen is locked move player back if hits top
				y3Vel = 4;
			else if (view.getCenter().y - y3 > MAX_TOP_PIXELS) //keep player from going -y direction
				y3Vel = 0;
			if (y3 - view.getCenter().y > MAX_BOTTOM_PIXELS) //keep player from going +y direction
				y3Vel = MOVE_SPEED + MOVE_OUT_OFF_SCREEN;
			if (x3 - view.getCenter().x > MAX_RIGHT_PIXELS) //keep player from going +x direction
				x3Vel = -PLAYER_X_VEL;
			if (view.getCenter().x - x3 > MAX_LEFT_PIXELS) //keep player from going -x direction
				x3Vel = PLAYER_X_VEL;
		}
	}

	//update player position based on velocities
	x1 += x1Vel;
	y1 += y1Vel;
	x2 += x2Vel;
	y2 += y2Vel;
	x3 += x3Vel;
	y3 += y3Vel;

	//update bounding boxes
	playerBox1.setPosition(x1, y1);
	playerBox2.setPosition(x2, y2);
	playerBox3.setPosition(x3, y3);
}

void Players::render(sf::RenderWindow& window, sf::Sprite planeS, sf::Sprite expS)
{
	//render players
	{
		//render player1
		if (alive1 == true)
		{
			//plane
			planeS.setScale(.6f, .9f);
			planeS.setPosition(sf::Vector2f(x1, y1));
			planeS.setTextureRect(sf::IntRect(318, 238, 107, 155));
			planeS.setColor(sf::Color(255, 255, 255, 255));
			if (invincible1 == false)
				window.draw(planeS);
			else if (invincible1 == true && flashInvincible % 2 == 0)
				window.draw(planeS);

			//plane shaddow
			planeS.setScale(.3f, .6f);
			planeS.setPosition(sf::Vector2f(x1 - 30, y1 + 120));
			planeS.setTextureRect(sf::IntRect(318, 638, 107, 155));
			planeS.setColor(sf::Color(255, 255, 255, 70));
			if (invincible1 == false)
				window.draw(planeS);
			else if (invincible1 == true && flashInvincible % 2 == 0)
				window.draw(planeS);

			/*
			*if not invincible render normally
			*otherwise render plane only every other game loop
			*/
			if (invincible1 == false && alive1 == true)
				window.draw(planeS);
			else if (invincible1 == true && flashInvincible % 2 == 0)
				window.draw(planeS);
		}

		//render player2
		if (alive2 == true)
		{
			//plane
			planeS.setScale(.6f, .9f);
			planeS.setPosition(sf::Vector2f(x2, y2));
			planeS.setTextureRect(sf::IntRect(830, 238, 113, 160));
			planeS.setColor(sf::Color(255, 255, 255, 255));
			if (invincible2 == false)
				window.draw(planeS);
			else if (invincible2 == true && flashInvincible % 2 == 0)
				window.draw(planeS);

			//plane shaddow
			planeS.setScale(.3f, .6f);
			planeS.setPosition(sf::Vector2f(x1 - 30, y1 + 120));
			planeS.setTextureRect(sf::IntRect(830, 635, 107, 155));
			planeS.setColor(sf::Color(255, 255, 255, 70));
			if (invincible1 == false && alive2 == true)
				window.draw(planeS);
			else if (invincible1 == true && flashInvincible % 2 == 0)
				window.draw(planeS);

			/*
			*if not invincible render normally
			*otherwise render plane only every other game loop
			*/
		}
		
		//render player3
		if (alive3 == true)
		{
			//plane
			planeS.setScale(.6f, .9f);
			planeS.setPosition(sf::Vector2f(x3, y3));
			planeS.setTextureRect(sf::IntRect(698, 241, 101, 154));	
			planeS.setColor(sf::Color(255, 255, 255, 255));
			if (invincible3 == false)
				window.draw(planeS);
			else if (invincible3 == true && flashInvincible % 2 == 0)
				window.draw(planeS);

			//plane shaddow
			planeS.setScale(.3f, .6f);
			planeS.setPosition(sf::Vector2f(x1 - 30, y1 + 120));
			planeS.setTextureRect(sf::IntRect(698, 640, 107, 155));
			planeS.setColor(sf::Color(255, 255, 255, 50));
			if (invincible3 == false && alive3 == true)
				window.draw(planeS);
			else if (invincible3 == true && flashInvincible % 2 == 0)
				window.draw(planeS);
			/*
			*if not invincible render normally
			*otherwise render plane only every other game loop
			*/
		}
	}

	//player died
	{
		if (alive1 == false && dead1 == false)
		{
			expS.setPosition(x1, y1);
			expS.setTextureRect(sf::IntRect(100 * explodeFrameX, 100 * explodeFrameY, 100, 100));
			explodeAnimate(dead1);
			window.draw(expS);
			overheat1 = 0;
		}

		if (menu.getPlayers() > 1)
		if (alive2 == false && dead2 == false)
		{
			expS.setPosition(x2, y2);
			expS.setTextureRect(sf::IntRect(100 * explodeFrameX, 100 * explodeFrameY, 100, 100));
			explodeAnimate(dead2);
			window.draw(expS);
			overheated2 = 0;
		}

		if (menu.getPlayers() > 2)
		if (alive3 == false && dead3 == false)
		{
			expS.setPosition(x3, y3);
			expS.setTextureRect(sf::IntRect(100 * explodeFrameX, 100 * explodeFrameY, 100, 100));
			explodeAnimate(dead3);
			window.draw(expS);
			overheat3 = 0;
		}
	}
	++flashInvincible;
}

void Players::HUD(sf::RenderWindow& window, sf::View& view, sf::Sprite& hud, sf::Font& font)
{
	//show score, health, lives, and missiles remaining for each player and gun overheating
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(FONT_SIZE);
	score.setColor(sf::Color::Black);

	sf::Text health;
	health.setFont(font);
	health.setCharacterSize(FONT_SIZE);
	health.setColor(sf::Color::Black);

	sf::Text lives;
	lives.setFont(font);
	lives.setCharacterSize(FONT_SIZE);
	lives.setColor(sf::Color::Black);

	sf::Text missile;
	missile.setFont(font);
	missile.setCharacterSize(FONT_SIZE);
	missile.setColor(sf::Color::Black);

	sf::Text weapon;
	weapon.setFont(font);
	weapon.setCharacterSize((FONT_SIZE - 4));
	weapon.setColor(sf::Color::Black);

	hud.setColor(sf::Color(255, 255, 255, 120)); //set HUD transparency
	hud.setScale(1.18f, 1.f); //set HUD scale

	if (coolDownTime1.asSeconds() <= 5)
		missileCoolDown1 = coolDownTime1.asSeconds() * 20;
	else
		missileCoolDown1 = 100;

	if (coolDownTime2.asSeconds() <= 5)
		missileCoolDown2 = coolDownTime2.asSeconds() * 20;
	else
		missileCoolDown2 = 100;

	if (coolDownTime3.asSeconds() <= 5)
		missileCoolDown3 = coolDownTime3.asSeconds() * 20;
	else
		missileCoolDown3 = 100;

	//player 1
	{
		//gun heat
		heatBar1.setPosition(x1, y1 - 15);
		heatBar1.setSize(sf::Vector2f(overheat1, 8));
		heatBar1.setFillColor(sf::Color((sf::Uint8)overheat1 + 100, 50, 255 - (sf::Uint8)(overheat1 * 2.5)));
		window.draw(heatBar1);

		//missile cooldown
		heatBar1.setPosition(x1 + 80, y1);
		heatBar1.setSize(sf::Vector2f(5, 100 - missileCoolDown1));
		heatBar1.setFillColor(sf::Color((sf::Uint8)overheat1 + 100, 50, 255 - (sf::Uint8)(missileCoolDown1 * 2.5)));
		window.draw(heatBar1);

		//HUD
		hud.setPosition(view.getCenter().x - 450, view.getCenter().y + 330);
		hud.setTextureRect(sf::IntRect(1, 1, 255, 166));
		window.draw(hud);

		//score
		std::stringstream scoreStream;
		scoreStream << showScore1;
		score.setString("Score: " + scoreStream.str());
		score.setPosition(view.getCenter().x - 430, view.getCenter().y + 350);
		window.draw(score);
		score.setString(std::string()); //clear score

		//health
		std::stringstream healthStream;
		healthStream << health1;
		health.setString("Health: " + healthStream.str());
		health.setPosition(view.getCenter().x - 430, view.getCenter().y + 370);
		window.draw(health);
		health.setString(std::string()); //clear health

		//lives
		std::stringstream liveStream;
		liveStream << lives1;
		lives.setString("Lives: " + liveStream.str());
		lives.setPosition(view.getCenter().x - 430, view.getCenter().y + 390);
		window.draw(lives);
		lives.setString(std::string()); //clear lives

		//missiles
		std::stringstream missileStream;
		missileStream << numMissile1 + bonusMissile1;
		missile.setString("Missiles: " + missileStream.str());
		missile.setPosition(view.getCenter().x - 430, view.getCenter().y + 410);
		window.draw(missile);
		missile.setString(std::string()); //clear missiles

		//current weapon
		if (gunType1 == machineGun)
			weapon.setString("  M");
		else if (gunType1 == homing)
		{
			std::stringstream weaponStream;
			weaponStream << "  H\n" << HOMING_GUN_BULLETS - bulletCount1;
			weapon.setString(weaponStream.str());
		}
		else if (gunType1 == dualGun)
		{
			std::stringstream weaponStream;
			weaponStream << "  D\n" << DUAL_GUN_BULLETS - bulletCount1;
			weapon.setString(weaponStream.str());
		}

		weapon.setPosition(view.getCenter().x - 250, view.getCenter().y + 378);
		window.draw(weapon);
		weapon.setString(std::string()); //clear current weapon
	}

	//player 2
	if (menu.getPlayers() > 1) //at least 2 playing
	{
		//gun heat
		heatBar2.setPosition(x2, y2 - 15);
		heatBar2.setSize(sf::Vector2f(overheat2, 8));
		heatBar2.setFillColor(sf::Color((sf::Uint8)overheat2 + 100, 50, 255 - (sf::Uint8)(overheat2 * 2.5)));
		window.draw(heatBar2);

		//missile cooldown
		heatBar2.setPosition(x2 + 80, y2);
		heatBar2.setSize(sf::Vector2f(5, 100 - missileCoolDown2));
		heatBar2.setFillColor(sf::Color((sf::Uint8)overheat2 + 100, 50, 255 - (sf::Uint8)(missileCoolDown2 * 2.5)));
		window.draw(heatBar2);

		//HUD
		hud.setPosition(view.getCenter().x - 150, view.getCenter().y + 330);
		hud.setTextureRect(sf::IntRect(256, 1, 255, 166));
		window.draw(hud);

		//score
		std::stringstream scoreStream;
		scoreStream << showScore2;
		score.setString("Score: " + scoreStream.str());
		score.setPosition(view.getCenter().x - 130, view.getCenter().y + 350);
		window.draw(score);
		score.setString(std::string()); //clear score

		//health
		std::stringstream healthStream;
		healthStream << health2;
		health.setString("Health: " + healthStream.str());
		health.setPosition(view.getCenter().x - 130, view.getCenter().y + 370);
		window.draw(health);
		health.setString(std::string()); //clear health

		//lives
		std::stringstream liveStream;
		liveStream << lives2;
		lives.setString("Lives: " + liveStream.str());
		lives.setPosition(view.getCenter().x - 130, view.getCenter().y + 390);
		window.draw(lives);
		lives.setString(std::string()); //clear lives

		//missiles
		std::stringstream missileStream;
		missileStream << numMissile2 + bonusMissile2;
		missile.setString("Missiles: " + missileStream.str());
		missile.setPosition(view.getCenter().x - 130, view.getCenter().y + 410);
		window.draw(missile);
		missile.setString(std::string()); //clear missiles

		//current weapon
		if (gunType2 == machineGun)
			weapon.setString("  M");
		else if (gunType2 == homing)
		{
			std::stringstream weaponStream;
			weaponStream << "  H\n" << HOMING_GUN_BULLETS - bulletCount2;
			weapon.setString(weaponStream.str());
		}
		else if (gunType2 == dualGun)
		{
			std::stringstream weaponStream;
			weaponStream << "  D\n" << DUAL_GUN_BULLETS - bulletCount2;
			weapon.setString(weaponStream.str());
		}

		weapon.setPosition(view.getCenter().x + 50, view.getCenter().y + 378);
		window.draw(weapon);
		weapon.setString(std::string()); //clear current weapon
	}

	//player 3
	if (menu.getPlayers() > 2) //3 playing
	{
		//gun heat
		heatBar3.setPosition(x3, y3 - 15);
		heatBar3.setSize(sf::Vector2f(overheat3, 8));
		heatBar3.setFillColor(sf::Color((sf::Uint8)overheat3 + 100, 50, 255 - (sf::Uint8)(overheat3 * 2.5)));
		window.draw(heatBar3);

		//missile cooldown
		heatBar3.setPosition(x3 + 80, y3);
		heatBar3.setSize(sf::Vector2f(5, 100 - missileCoolDown3));
		heatBar3.setFillColor(sf::Color((sf::Uint8)overheat3 + 100, 50, 255 - (sf::Uint8)(missileCoolDown3 * 2.5)));
		window.draw(heatBar3);

		//HUD
		hud.setPosition(view.getCenter().x + 150, view.getCenter().y + 330);
		hud.setTextureRect(sf::IntRect(511, 1, 255, 166));
		window.draw(hud);

		//score
		std::stringstream scoreStream;
		scoreStream << showScore3;
		score.setString("Score: " + scoreStream.str());
		score.setPosition(view.getCenter().x + 170, view.getCenter().y + 350);
		window.draw(score);
		score.setString(std::string()); //clear score

		//health
		std::stringstream healthStream;
		healthStream << health3;
		health.setString("Health: " + healthStream.str());
		health.setPosition(view.getCenter().x + 170, view.getCenter().y + 370);
		window.draw(health);
		health.setString(std::string()); //clear health

		//lives
		std::stringstream liveStream;
		liveStream << lives3;
		lives.setString("Lives: " + liveStream.str());
		lives.setPosition(view.getCenter().x + 170, view.getCenter().y + 390);
		window.draw(lives);
		lives.setString(std::string()); //clear lives

		//missiles
		std::stringstream missileStream;
		missileStream << numMissile3 + bonusMissile3;
		missile.setString("Missiles: " + missileStream.str());
		missile.setPosition(view.getCenter().x + 170, view.getCenter().y + 410);
		window.draw(missile);
		missile.setString(std::string()); //clear missiles

		//current weapon
		if (gunType3 == machineGun)
			weapon.setString("  M");
		else if (gunType3 == homing)
		{
			std::stringstream weaponStream;
			weaponStream << "  H\n" << HOMING_GUN_BULLETS - bulletCount3;
			weapon.setString(weaponStream.str());
		}
		else if (gunType3 == dualGun)
		{
			std::stringstream weaponStream;
			weaponStream << "  D\n" << DUAL_GUN_BULLETS - bulletCount3;
			weapon.setString(weaponStream.str());
		}

		weapon.setPosition(view.getCenter().x + 350, view.getCenter().y + 378);
		window.draw(weapon);
		weapon.setString(std::string()); //clear current weapon
	}
}

void Players::explodeAnimate(bool& dead)
{
	if (explodeFrameX > 9)
	{
		++explodeFrameY;
		explodeFrameX = 0;
	}

	if (explodeFrameY == 8 && explodeFrameX > 2)
	{
		explodeFrameX = 0;
		explodeFrameY = 0;
		dead = true;
	}

	++explodeFrameX;
}

void Players::overheat(float& overheatAmount, bool& overheated, bool& fire, int gunType)
{
	if (overheatAmount > 0) //gun cool down
		overheatAmount -= .2f;
	else if (overheatAmount < 0) //keep from going below 0
		overheatAmount = 0;

	if (fire == true) //gun heat up
	{
		if (gunType == machineGun)
			overheatAmount += .4f;
		else if (gunType == homing)
			overheatAmount += .35f;
		else if (gunType == dualGun)
			overheatAmount += .55f;
	}

	if (overheatAmount >= 100)
	{
		overheatAmount = 100;
		overheated = true;
	}

	if (overheated == true)
	{
		if (overheatAmount == 0)
			overheated = false;
	}
}

void Players::getFiring(bool& fire1, bool& fire2, bool& fire3, bool& missile1, bool& missile2, bool& missile3)
{
	/*
	*get if player if firing gun
	*prevent player from firing if gun is overheating
	*/
	if (overheated1 == false)
		fire1 = this->fire1;
	else
		fire1 = false;

	if (overheated2 == false)
		fire2 = this->fire2;
	else
		fire2 = false;

	if (overheated3 == false)
		fire3 = this->fire3;
	else
		fire3 = false;

	missile1 = this->missile1;
	missile2 = this->missile2;
	missile3 = this->missile3;

	//sets gun heat level
	overheat(overheat1, overheated1, fire1, gunType1);
	overheat(overheat2, overheated2, fire2, gunType2);
	overheat(overheat3, overheated3, fire3, gunType3);

	if (gunType1 == homing)
	{
		if (fire1 == true)
			++bulletCount1;

		if (bulletCount1 >= HOMING_GUN_BULLETS)
		{
			bulletCount1 = 0;
			gunType1 = machineGun;
			overheat1 = 0;
		}
	}
	else if (gunType1 == dualGun)
	{
		if (fire1 == true)
			++bulletCount1;

		if (bulletCount1 >= DUAL_GUN_BULLETS)
		{
			bulletCount1 = 0;
			gunType1 = machineGun;
			overheat1 = 0;
		}
	}

	if (gunType2 == homing)
	{
		if (fire2 == true)
			++bulletCount2;

		if (bulletCount2 >= HOMING_GUN_BULLETS)
		{
			bulletCount2 = 0;
			gunType2 = machineGun;
			overheat2 = 0;
		}
	}
	else if (gunType2 == dualGun)
	{
		if (fire2 == true)
			++bulletCount2;

		if (bulletCount2 >= DUAL_GUN_BULLETS)
		{
			bulletCount2 = 0;
			gunType2 = machineGun;
			overheat2 = 0;
		}
	}

	if (gunType3 == homing)
	{
		if (fire3 == true)
			++bulletCount3;

		if (bulletCount3 >= HOMING_GUN_BULLETS)
		{
			bulletCount3 = 0;
			gunType3 = machineGun;
			overheat3 = 0;
		}
	}
	else if (gunType3 == dualGun)
	{
		if (fire3 == true)
			++bulletCount3;

		if (bulletCount3 >= DUAL_GUN_BULLETS)
		{
			bulletCount3 = 0;
			gunType3 = machineGun;
			overheat3 = 0;
		}
	}
}

void Players::getXY(float& x1, float& y1, float& x2, float& y2, float& x3, float& y3)
{
	//get plane position
	x1 = this->x1;
	y1 = this->y1;

	x2 = this->x2;
	y2 = this->y2;

	x3 = this->x3;
	y3 = this->y3;
}

void Players::kill(int playerNum)
{
	switch (playerNum)
	{
	case player1: //kill player 1
		health1 = PLAYER_HEALTH;
		numMissile1 = STARTING_MISSILES;
		bonusMissile1 = 0;
		coolDownTime1 = sf::seconds(6);
		alive1 = false;
		fire1 = false;
		invincible1 = true;
		invincibleClock1.restart();
		gunType1 = machineGun;
		bulletCount1 = 0;

		//disable collision box
		playerBox1.setPosition(-1000, -1000);
		break;

	case player2: //kill player 2
		health2 = PLAYER_HEALTH;
		numMissile2 = STARTING_MISSILES;
		bonusMissile2 = 0;
		coolDownTime2 = sf::seconds(6);
		alive2 = false;
		fire2 = false;
		invincible2 = true;
		invincibleClock2.restart();
		gunType2 = machineGun;
		bulletCount2 = 0;

		//disable collision box
		playerBox2.setPosition(-1000, -1000);
		break;

	case player3: //kill player 3
		health3 = PLAYER_HEALTH;
		numMissile3 = STARTING_MISSILES;
		bonusMissile3 = 0;
		coolDownTime3 = sf::seconds(6);
		alive3 = false;
		fire3 = false;
		invincible3 = true;
		invincibleClock3.restart();
		gunType3 = machineGun;	
		bulletCount3 = 0;

		//disable collision box
		playerBox3.setPosition(-1000, -1000);
		break;
	};
}

void Players::useLife()
{
	/*
	*if a player dies
	*decrement life by one if lives is greater than 0
	*then restore player
	*/

	if (dead1 == true)
		if (lives1 > 0)
		{
			--lives1;
			alive1 = true;
			dead1 = false;
		}

	if (dead2 == true)
		if (lives2 > 0)
		{
			--lives2;
			alive2 = true;
			dead2 = false;
		}

	if (dead3 == true)
		if (lives3 > 0)
		{
			--lives3;
			alive3 = true;
			dead3 = false;
		}
}

bool Players::getAlive(int playerNum)
{
	switch (playerNum)
	{
	case player1: //player 1
		return alive1;
		break;

	case player2: //player 2
		return alive2;
		break;

	case player3: //player 3
		return alive3;
		break;
	};

	return NULL;
}

bool Players::getInvincible(int playerNum)
{
	/*
	*returns state of invincibility temporarily if
	*player has died
	*/
	switch (playerNum)
	{
	case player1: //player 1		
		return invincible1;
		break;

	case player2: //player 2		
		return invincible2;
		break;

	case player3: //player 3		
		return invincible3;
		break;
	};
	return false;
}

void Players::changeInvincible()
{
	//change player to not invincible after time
	invincibleTimer1 = invincibleClock1.getElapsedTime();
	invincibleTimer2 = invincibleClock2.getElapsedTime();
	invincibleTimer3 = invincibleClock3.getElapsedTime();

	//if timer has reached limit set invincible to false
	if (invincible1 == true && invincibleTimer1.asSeconds() > INVINCIBILITY_TIME)
		invincible1 = false;
	
	if (invincible2 == true && invincibleTimer2.asSeconds() > INVINCIBILITY_TIME)
		invincible2 = false;
	
	if (invincible3 == true && invincibleTimer3.asSeconds() > INVINCIBILITY_TIME)
		invincible3 = false;
	
}

void Players::setScore(int playerNum, int amount, sf::Sound& lifeUp)
{
	if (playerNum == player1)
	{
		score1 += amount;
		showScore1 += amount;

		if (score1 >= INCREASE_LIVES_SCORE)
		{
			lifeUp.play();
			score1 = 0;
			++lives1;
		}
	}
	if (playerNum == player2)
	{
		score2 += amount;
		showScore2 += amount;

		if (score2 >= INCREASE_LIVES_SCORE)
		{
			lifeUp.play();
			score2 = 0;
			++lives2;
		}
	}
	if (playerNum == player3)
	{
		score3 += amount;
		showScore3 += amount;

		if (score3 >= INCREASE_LIVES_SCORE)
		{
			lifeUp.play();
			score3 = 0;
			++lives3;
		}
	}
}

void Players::reset()
{
	//set starting player coords
	x1 = 100;
	y1 = PLAYER_START_LOCATION + 100;
	x2 = 500;
	y2 = PLAYER_START_LOCATION;
	x3 = 800;
	y3 = PLAYER_START_LOCATION + 100;

	//set default player velocities
	x1Vel = 0;
	y1Vel = 0;
	x2Vel = 0;
	y2Vel = 0;
	x3Vel = 0;
	y3Vel = 0;

	//player alive
	alive1 = true;
	alive2 = true;
	alive3 = true;

	//player dead
	dead1 = false;
	dead2 = false;
	dead3 = false;

	//set invincible
	invincible1 = false;
	invincible2 = false;
	invincible3 = false;
	flashInvincible = 0;

	//set player lives
	lives1 = PLAYER_STARTING_LIVES;
	lives2 = PLAYER_STARTING_LIVES;
	lives3 = PLAYER_STARTING_LIVES;

	//set player health
	health1 = PLAYER_HEALTH;
	health2 = PLAYER_HEALTH;
	health3 = PLAYER_HEALTH;

	//reset missiles
	numMissile1 = STARTING_MISSILES;
	numMissile2 = STARTING_MISSILES;
	numMissile3 = STARTING_MISSILES;
	bonusMissile1 = 0;
	bonusMissile2 = 0;
	bonusMissile3 = 0;
	coolDownTime1 = sf::seconds(6);
	coolDownTime2 = sf::seconds(6);
	coolDownTime3 = sf::seconds(6);

	//bounding boxes
	playerBox1.setPosition(this->x1, this->y1);
	playerBox2.setPosition(this->x2, this->y2);
	playerBox3.setPosition(this->x3, this->y3);

	//set explosion frame to 0
	explodeFrameX = 0;
	explodeFrameY = 0;

	//set score
	score1 = 0;
	score2 = 0;
	score3 = 0;
	showScore1 = 0;
	showScore2 = 0;
	showScore3 = 0;

	//gun overheat
	overheat1 = 0;
	overheat2 = 0;
	overheat3 = 0;
	overheated1 = false;
	overheated2 = false;
	overheated3 = false;

	//set gun type
	gunType1 = machineGun;
	gunType2 = machineGun;
	gunType3 = machineGun;

	//upgrade bullet count
	bulletCount1 = 0;
	bulletCount2 = 0;
	bulletCount3 = 0;
}

void Players::setPlayers()
{
	//disable extra player slots not in use
	if (menu.getPlayers() < 3)
	{
		lives3 = 0;
		alive3 = false;
	}

	if (menu.getPlayers() < 2)
	{
		lives2 = 0;
		alive2 = false;
	}
}

sf::Vector2f Players::getPlayerPos(int player)
{
	sf::Vector2f currentPos;

	switch (player)
	{
	case player1:
		currentPos.x = x1;
		currentPos.y = y1;
		break;

	case player2:
		currentPos.x = x2;
		currentPos.y = y2;
		break;

	case player3:
		currentPos.x = x3;
		currentPos.y = y3;
		break;
	};
	return currentPos;
}

void Players::subHealth(int hitAmount, int player)
{
	switch (player)
	{
	case player1:
		health1 -= hitAmount;
		break;

	case player2:
		health2 -= hitAmount;
		break;

	case player3:
		health3 -= hitAmount;
		break;
	};
}

void Players::addHealth(int player)
{
	switch (player)
	{
	case player1:
		health1 += HEAL_ITEM;
		if (health1 > PLAYER_HEALTH)
			health1 = PLAYER_HEALTH;
		break;

	case player2:
		health2 += HEAL_ITEM;
		if (health2 > PLAYER_HEALTH)
			health2 = PLAYER_HEALTH;
		break;

	case player3:
		health3 += HEAL_ITEM;
		if (health3 > PLAYER_HEALTH)
			health3 = PLAYER_HEALTH;
		break;
	};
}

int Players::getHealth(int player)
{
	int currentHealth = 0;
	switch (player)
	{
	case player1:
		currentHealth = health1;
		break;

	case player2:
		currentHealth = health2;
		break;

	case player3:
		currentHealth = health3;
		break;
	};
	return currentHealth;
}

int Players::getEquippedGunType(int player)
{
	/*
	*returns current player equipped gun type
	*for use in bullet object's behavior
	*/
	switch (player)
	{
	case player1:
		return gunType1;
		break;

	case player2:
		return gunType2;
		break;

	case player3:
		return gunType3;
		break;
	};

	return 0;
}

void Players::setGunType(int type, int player)
{
	/*
	*set current player gun type
	*for item pickups
	*set count to zero, even if alrady equipped to replenish ammo
	*set heat back to 0, if did not already have new weapon type
	*/
	switch (player)
	{
	case player1:
		if (gunType1 != type)
			overheat1 = 0;
		gunType1 = type;
		bulletCount1 = 0;
		break;

	case player2:
		if (gunType2 != type)
			overheat2 = 0;
		gunType2 = type;
		bulletCount2 = 0;	
		break;

	case player3:
		if (gunType3 != type)
			overheat3 = 0;
		gunType3 = type;
		bulletCount3 = 0;
		break;
	};
}

void Players::incMissiles(int player)
{
	switch (player)
	{
	case player1:
		++bonusMissile1;
		break;

	case player2:
		++bonusMissile2;
		break;

	case player3:
		++bonusMissile3;
		break;
	};
}

void Players::setLives(const int& player, const int& life)
{
	switch (player)
	{
	case player1:
		lives1 += life;
		break;

	case player2:
		lives2 += life;
		break;

	case player3:
		lives3 += life;
		break;
	};
}

int Players::getLives(const int& player)
{
	switch (player)
	{
	case player1:
		return lives1;
		break;

	case player2:
		return lives2;
		break;

	case player3:
		return lives3;
		break;
	};

	return 0;
}

void Players::nextLevelReset()
{
	//set starting player coords
	x1 = 100;
	y1 = PLAYER_START_LOCATION;
	x2 = 500;
	y2 = PLAYER_START_LOCATION;
	x3 = 800;
	y3 = PLAYER_START_LOCATION;

	//set heat levels to 0
	overheat1 = 0;
	overheat2 = 0;
	overheat3 = 0;
}

void Players::lockScreenPos(bool lock)
{
	lockScreen = lock;
}

int Players::getScore(const int& player)
{
	switch (player)
	{
	case player1:
		return showScore1;
		break;

	case player2:
		return showScore2;
		break;

	case player3:
		return showScore3;
		break;
	};
	return 0;
}