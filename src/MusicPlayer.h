#pragma once
#include <SFML/Audio.hpp>

class MusicPlayer
{
public:
	MusicPlayer();
	void play(const int& levelState, bool& startMusic, sf::Music& music);
	void stop(sf::Music& music);
};