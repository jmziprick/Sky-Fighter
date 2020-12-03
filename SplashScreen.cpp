#include "SplashScreen.h"

int SplashScreen::frame = 0;

SplashScreen::SplashScreen()
{
	playSound = true;
	stopSpin = false;
	playingVideo = false;

	spinRate = 0;

	videoView.setSize(1280, 720);
}

bool SplashScreen::display(sf::RenderWindow& window, sf::Sprite& splash, sf::Sound& splashSound, sfe::Movie& openingMovie)
{
	if (!playingVideo)
	{
		splash.setScale(sf::Vector2f(.5, .5));

		time = clock.getElapsedTime();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed)
			{
				splashSound.stop();
				playingVideo = true;
			}
		}

		splash.setTextureRect(sf::IntRect(0, (118 * frame) + 1, 1548, 118));

		if (spinRate > 100 && frame == 0)
			stopSpin = true;

		if (time.asMilliseconds() > spinRate && spinRate && stopSpin == false)
		{
			clock.restart();
			frame++;
		}

		if (frame > 29)
			frame = 0;

		splash.setPosition(-200, -100);
		window.draw(splash);

		if (splashSound.getPlayingOffset().asSeconds() > 14)
			playingVideo = true;

		if (playSound)
		{
			splashSound.play();
			playSound = false;
		}

		if (frame % 2 == 0)
			spinRate++;
	}

	//video
	if (playingVideo)
	{
		window.setView(videoView);
		openingMovie.play();
		openingMovie.resizeToFrame(0, 0, 1280, 720);
		openingMovie.setScale(1.f, 1.32f);
		openingMovie.setPosition(-140, 25);

		playingVideo = false;
	}

	while (openingMovie.getStatus() == sfe::Movie::Playing)
	{
		while (window.pollEvent(event))
		{
			sf::Joystick::update();
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed)
				if (event.key.code == sf::Keyboard::Escape || sf::Joystick::isButtonPressed(0, Start))
				{
					openingMovie.stop();
					return false;
				}
		}

		window.clear();
		window.draw(openingMovie);
		window.display();

		if (openingMovie.getStatus() != sfe::Movie::Playing)
			return false;
	}

	return true;
}