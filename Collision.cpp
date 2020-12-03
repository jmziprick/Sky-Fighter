#include "Collision.h"
#include <iostream>
bool collision(sf::Vector2f xy1, sf::Vector2f wh1, sf::Vector2f xy2, sf::Vector2f wh2)
{
	float topA = xy1.y;
	float topB = xy2.y;
	float bottomA = xy1.y + wh1.y;
	float bottomB = xy2.y + wh2.y;
	float rightA = xy1.x + wh1.x;
	float rightB = xy2.x + wh2.x;
	float leftA = xy1.x;
	float leftB = xy2.x;

	if (topA >= bottomB)
		return false;
	if (bottomA <= topB)
		return false;
	if (leftA >= rightB)
		return false;
	if (rightA <= leftB)
		return false;

	return true;
}