#include "MusicPlayer.h"


MusicPlayer::MusicPlayer()
{
}

void MusicPlayer::play(const int& levelState, bool& startMusic, sf::Music& music)
{
	if (levelState == 0 && startMusic == true)
	{
		startMusic = false;
		music.openFromFile("Music/intro.wav");
		music.setLoop(true);
		music.play();
	}

	if (levelState == 1 && startMusic == true)
	{
		startMusic = false;
		music.openFromFile("Music/level 1.wav");
		music.setLoop(true);
		music.play();
	}

	if (levelState == 2 && startMusic == true)
	{
		startMusic = false;
		music.openFromFile("Music/level 2.wav");
		music.setLoop(true);
		music.play();
	}
}

void MusicPlayer::stop(sf::Music& music)
{
	music.stop();
}