#include "Particle.h"


Particle::Particle()
{
	vertexParticles.setPrimitiveType(sf::PrimitiveType::Points);
}

void Particle::createSmallExplosion(sf::Vector2f pos)
{
	bool randomParticleEffect = false; //do not randomize effects

	//create new particles at pos
	for (unsigned int i = 0; i < PARTICLES_SMALL_EXPLOSION; ++i)
	{
		Particles* particles = new Particles(pos, randomParticleEffect);
		particlesVector.push_back(particles);
	}

	vertexParticles.resize(particlesVector.size());


	for (unsigned int i = 0; i < particlesVector.size(); ++i)
		vertexParticles[i].color = sf::Color(particlesVector.at(i)->r, particlesVector.at(i)->g, particlesVector.at(i)->b);
}

void Particle::createMediumExplosion(sf::Vector2f pos)
{
	bool randomParticleEffect = true; //randomize effects

	//create new particles at pos
	for (unsigned int i = 0; i < PARTICLES_MEDIUM_EXPLOSION; ++i)
	{
		Particles* particles = new Particles(pos, randomParticleEffect);
		particlesVector.push_back(particles);
	}

	vertexParticles.resize(particlesVector.size());


	for (unsigned int i = 0; i < particlesVector.size(); ++i)
		vertexParticles[i].color = sf::Color(particlesVector.at(i)->r, particlesVector.at(i)->g, particlesVector.at(i)->b);
}

void Particle::createBigExplosion(sf::Vector2f pos)
{
	bool randomParticleEffect = true; //randomize effects

	//create new particles at pos
	for (unsigned int i = 0; i < PARTICLES_BIG_EXPLOSION; ++i)
	{
		Particles* particles = new Particles(pos, randomParticleEffect);
		particlesVector.push_back(particles);
	}

	vertexParticles.resize(particlesVector.size());


	for (unsigned int i = 0; i < particlesVector.size(); ++i)
		vertexParticles[i].color = sf::Color(particlesVector.at(i)->r, particlesVector.at(i)->g, particlesVector.at(i)->b);
}

void Particle::update(sf::RenderWindow& window)
{
	bool resizeVertex = false;
	//update particles
	for (unsigned int i = 0; i < particlesVector.size(); ++i)
	{
		particlesVector.at(i)->update(); //update particle data

		//update particle vertex
		vertexParticles[i].position.x = particlesVector.at(i)->pos.x;
		vertexParticles[i].position.y = particlesVector.at(i)->pos.y;

		if (particlesVector.at(i)->alive == false)
		{
			delete particlesVector.at(i);
			particlesVector.erase(particlesVector.begin() + i);
			resizeVertex = true;
		}
	}

	if (resizeVertex == true)
		vertexParticles.resize(particlesVector.size());
	
	window.draw(vertexParticles);
}
