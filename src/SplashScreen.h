#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sfeMovie/Movie.hpp>
#include "Constants.h"

class SplashScreen
{
public:
	SplashScreen();
	bool display(sf::RenderWindow& window, sf::Sprite& splash, sf::Sound& splashSound, sfe::Movie& openingMovie);

private:
	sf::View videoView;

	sf::SoundBuffer splashSoundBuff;
	sf::Sound splashSound;

	bool playSound;
	bool playingVideo;

	sf::Event event;

	static int frame;

	sf::Clock clock; //frame limiter
	sf::Time time;

	int spinRate;
	bool stopSpin;
};

