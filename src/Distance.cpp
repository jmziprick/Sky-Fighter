#include "Distance.h"

float getDistance(sf::Vector2f firstPos, sf::Vector2f secondPos)
{
	/*
	*compares two position coordinates
	*gets their distances (x, y) and
	*adds them into a total value representing
	*the total distance of the object from the first
	*/

	float xDistance;
	float yDistance;
	float totalDistance;

	if (firstPos.x > secondPos.x)	
		xDistance = firstPos.x - secondPos.x;
	else if (firstPos.x < secondPos.x)
		xDistance = secondPos.x - firstPos.x;

	if (firstPos.y > secondPos.y)
		yDistance = firstPos.y - secondPos.y;
	else if (firstPos.y < secondPos.y)
		yDistance = secondPos.y - firstPos.y;

	totalDistance = xDistance + yDistance;

	return totalDistance;
}

bool cmpEnemyDToBossD(sf::Vector2f player, sf::Vector2f enemy, sf::Vector2f boss)
{
	/*
	*compares two position coordinates
	*returns true if boss is less distance than enemy
	*/
	float totalDistanceEnemy;
	float totalDistanceBoss;

	totalDistanceEnemy = getDistance(player, enemy);
	totalDistanceBoss = getDistance(player, boss);

	if (totalDistanceBoss < totalDistanceEnemy)
		return true;
	else
		return false;
}