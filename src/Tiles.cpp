#include "Tiles.h"


Tiles::Tiles()
{
	tileMap.setPrimitiveType(sf::Quads);
	tileMap.resize((LEVEL_HEIGHT * LEVEL_WIDTH) * 4); //(25 * 9000) * 4 == 500000
}

void Tiles::createMap(int map[LEVEL_HEIGHT][LEVEL_WIDTH])
{
	int vertice = 0;

	for (int h = 0; h < LEVEL_HEIGHT; ++h)
	{
		for (int w = 0; w < LEVEL_WIDTH; ++w)
		{
			//if ()
			{

				int tileType = map[h][w]; //set tileType to tile specified on map array, for setting vertex texture coords

				/*
				*create quad vertices using height,
				*and width of map (25width x 1000height)
				*
				*-NOTE- declare all vertices in clockwise direction
				*starting with top left
				*/

				tileMap[0 + vertice].position = (sf::Vector2f(w * 48.f, h * 48.f));
				tileMap[1 + vertice].position = (sf::Vector2f(w * 48.f + 48, h * 48.f));
				tileMap[2 + vertice].position = (sf::Vector2f(w * 48.f + 48, h * 48.f + 48));
				tileMap[3 + vertice].position = (sf::Vector2f(w * 48.f, h * 48.f + 48));

				/*
				*set texture coordinates to each quad
				*using tileType to define which texture to use
				*from tilemap image file, again declaring
				*in clockwise direction
				*/

				switch (tileType)
				{
				case jungle:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(0, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(48, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(48, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(0, 48));
					break;

				case sand:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(48, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(96, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(96, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(48, 48));
					break;

				case tent:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(96, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(144, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(144, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(96, 48));
					break;

				case bigRock:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(144, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(192, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(192, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(144, 48));
					break;

				case cactus:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(192, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(240, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(240, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(192, 48));
					break;

				case smallRock:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(240, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(288, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(288, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(240, 48));
					break;

				case smallCactus:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(288, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(336, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(336, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(288, 48));
					break;

				case topLJungle:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(336, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(384, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(384, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(336, 48));
					break;

				case topRJungle:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(384, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(432, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(432, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(384, 48));
					break;

				case bottomJungleWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(432, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(480, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(480, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(432, 48)); //--------
					break;

				case topJungleWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(480, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(528, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(528, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(480, 48));
					break;

				case leftJungleSand:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(528, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(576, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(576, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(528, 48));
					break;

				case topJungleSand:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(576, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(624, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(624, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(576, 48));
					break;

				case topSandWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(624, 0));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(672, 0));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(672, 48));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(624, 48));
					break;

				case bottomLCliff:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(0, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(48, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(48, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(0, 96));
					break;

				case botomRCliff:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(48, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(96, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(96, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(48, 96));
					break;

				case topRCliff:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(96, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(144, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(144, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(96, 96));
					break;

				case topLCliff:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(144, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(192, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(192, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(144, 96));
					break;

				case bigPalm:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(192, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(240, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(240, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(192, 96));
					break;

				case smallJPalm:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(240, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(288, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(288, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(240, 96));
					break;

				case water:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(288, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(336, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(336, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(288, 96));
					break;

				case botomLJungle:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(336, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(384, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(384, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(336, 96));
					break;

				case bottomRJungle:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(384, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(432, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(432, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(384, 96));
					break;

				case empty1:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(432, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(480, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(480, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(432, 96));
					break;

				case rightJungleSand:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(480, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(528, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(528, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(480, 96));
					break;

				case rightJungleWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(528, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(576, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(576, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(528, 96));
					break;

				case bottomJungleSand:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(576, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(624, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(624, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(576, 96));
					break;

				case leftSandWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(624, 48));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(672, 48));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(672, 96));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(624, 96));
					break;

				case topLWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(0, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(48, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(48, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(0, 144));
					break;

				case topRWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(48, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(96, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(96, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(48, 144));
					break;

				case bottomLWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(96, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(144, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(144, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(96, 144));
					break;

				case bottomRWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(144, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(192, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(192, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(144, 144));
					break;

				case topLJungleWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(192, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(240, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(240, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(192, 144));
					break;

				case topRJungleWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(240, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(288, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(288, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(240, 144));
					break;

				case bottomLJungleWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(288, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(336, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(336, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(288, 144));
					break;

				case bottomRJungleWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(336, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(384, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(384, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(336, 144));
					break;

				case empty4:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(384, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(432, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(432, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(384, 144));
					break;

				case empty2:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(432, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(480, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(480, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(432, 144));
					break;

				case empty3:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(480, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(528, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(528, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(480, 144));
					break;

				case leftJungleWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(528, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(576, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(576, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(528, 144));
					break;

				case bottomSandWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(576, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(624, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(624, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(576, 144));
					break;

				case rightSandWater:
					tileMap[0 + vertice].texCoords = (sf::Vector2f(624, 96));
					tileMap[1 + vertice].texCoords = (sf::Vector2f(672, 96));
					tileMap[2 + vertice].texCoords = (sf::Vector2f(672, 144));
					tileMap[3 + vertice].texCoords = (sf::Vector2f(624, 144));
					break;

				default:
					tileMap[0 + vertice].color = sf::Color::Black;
					tileMap[1 + vertice].color = sf::Color::Black;
					tileMap[2 + vertice].color = sf::Color::Black;
					tileMap[3 + vertice].color = sf::Color::Black;
				};
				vertice += 4; //go to next set of vertices
			}
		}
	}
	vertice = 0;
}

sf::VertexArray Tiles::getMapVA()
{
	return tileMap;
}