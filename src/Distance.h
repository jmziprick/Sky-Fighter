#ifndef DISTANCE_H
#define DISTANCE_H

#include <SFML/Graphics.hpp>

float getDistance(sf::Vector2f firstPos, sf::Vector2f secondPos);
bool cmpEnemyDToBossD(sf::Vector2f player, sf::Vector2f enemy, sf::Vector2f boss);

#endif