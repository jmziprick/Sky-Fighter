#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Tiles
{
public:
	Tiles();
	void createMap(int map[1000][25]);
	sf::VertexArray getMapVA();

private:
	sf::VertexArray tileMap;
	enum tileTypes {empty, jungle, sand, tent, bigRock, cactus, smallRock, smallCactus, topLJungle, topRJungle, bottomJungleWater, topJungleWater,
	leftJungleSand, topJungleSand, topSandWater, bottomLCliff, botomRCliff, topRCliff, topLCliff, bigPalm, smallJPalm, water, botomLJungle, bottomRJungle, empty1,
	rightJungleSand, rightJungleWater, bottomJungleSand, leftSandWater, topLWater, topRWater, bottomLWater, bottomRWater, topLJungleWater, topRJungleWater, bottomLJungleWater,
	bottomRJungleWater, empty4, empty2, empty3, leftJungleWater, bottomSandWater, rightSandWater};
};

