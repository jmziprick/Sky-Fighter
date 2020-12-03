#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"

class Particle
{
public:
	Particle();
	void update(sf::RenderWindow& window);		
	void createSmallExplosion(sf::Vector2f pos);
	void createMediumExplosion(sf::Vector2f pos);
	void createBigExplosion(sf::Vector2f pos);

private:
	struct Particles
	{
		Particles(sf::Vector2f startPoints, bool randomParticleEffect)
		{
			alive = true;
			start = startPoints;

			float angle = (float)((std::rand() % 360) * 3.14 / 180.f);
			float speed = (float)(std::rand() % 5);

			vel = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);


			pos.x = startPoints.x += (float)(std::cos((std::rand() % 360) * 3.14 / 180.f) + std::rand() % 20);
			pos.y = startPoints.y += (float)(std::sin((std::rand() % 360) * 3.14 / 180.f) + std::rand() % 20);

			//particle colors
			if (randomParticleEffect == false)
			{
				//set color to yellow
				r = 255;
				g = 255;
				b = 125;
				alpha = 255;

				float speed = (float)(std::rand() % 10 + 10);
			}
			else if (randomParticleEffect == true)
			{
				selectedColor = std::rand() % 5;

				switch (selectedColor)
				{
				case orange:
					r = 255;
					g = 85;
					b = 0;
					alpha = 255;
					break;

				case black:
					r = 0;
					g = 0;
					b = 0;
					alpha = 255;
					break;

				case silver:
					r = 115;
					g = 115;
					b = 115;
					alpha = 255;
					break;

				case yellow:
					r = 255;
					g = 255;
					b = 125;
					alpha = 255;
					break;

				case white:
					r = 255;
					g = 255;
					b = 255;
					alpha = 255;
					break;
				};
			}
		}

		void update()
		{		
			lifeTime = lifeClock.getElapsedTime();

			//move
			pos.x += vel.x;
			pos.y += vel.y;

			//distance from start point
			float distanceX = pos.x - start.x;
			float distanceY = pos.y - start.y;

			//if absolute distance from start is greater than 100 dec. alpha
			if (std::abs(distanceX) >= 100 || std::abs(distanceY) >= 100)
				alpha -= 10;
			if (alpha < 0)
				alpha = 0;

			//kill particle after time
			if (lifeTime.asMilliseconds() >= PARTICLE_LIFETIME)
				alive = false;
		}

		sf::Clock lifeClock;
		sf::Time lifeTime;

		sf::Vector2f vel;
		sf::Vector2f pos;
		sf::Vector2f start;

		int r, g, b, alpha; //RGB and alpha values
		int selectedColor; //current particle color
		enum colors{orange, black, silver, yellow, white}; //particle color types

		bool alive;
	};

	sf::VertexArray vertexParticles;
	std::vector<Particles*> particlesVector;
};

