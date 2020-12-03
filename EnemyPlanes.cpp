#include "EnemyPlanes.h"


EnemyPlanes::EnemyPlanes(const sf::View& view, Menu& menu) : Enemies()
{
	//set plane type
	planeType = rand() % 3;
	//if mig51s 66% chance of other plane type
	if (planeType == mig51s)
		planeType = rand() % 3;

	//set starting position
	x = (float)(rand() % 900 + 100);
	y = (float)(view.getCenter().y - 500);

	//bounding box, health, and score 
	if (planeType == mig51s)
	{
		enemyBox.setSize(sf::Vector2f(65, 115));
		enemyBox.setPosition(x - 65, y - 115);
		health = MIG51S_HEALTH + (menu.getPlayers() - 1) * 15; //scale health depending on how many players there are active
		scoreAmount = MIG51S_SCORE;
	}
	else if (planeType == su37k)
	{
		enemyBox.setSize(sf::Vector2f(65, 115));
		enemyBox.setPosition(x - 73, y - 125);
		health = SU37K_HEALTH + (menu.getPlayers() - 1) * 15; //scale health depending on how many players there are active
		scoreAmount = SU37K_SCORE;
	}
	else if (planeType == mig51)
	{
		enemyBox.setSize(sf::Vector2f(65, 126));
		enemyBox.setPosition(x - 70, y - 152);
		health = MIG51_HEALTH + (menu.getPlayers() - 1) * 15; //scale health depending on how many players there are active
		scoreAmount = MIG51_SCORE;
	}

	alive = true; //enemy alive
	dead = false; //enemy dead

	//set explosion frame to 0
	explodeFrameX = 0;
	explodeFrameY = 0;

	fire = false; //set firing gun to false

	//plane direction
	direction = rand() % 2;

	//set plane move type
	moveType = rand() % 2;
}

void EnemyPlanes::move(sf::View& view)
{
	y += ENEMY_Y_VEL;

	//if enemy is move type, change flying direction back and forth
	enum type { no, yes };
	if (moveType == yes)
	{

		if (direction == left)
			x -= ENEMY_X_VEL;
		else if (direction == right)
			x += ENEMY_X_VEL;
	}


	if (x - view.getCenter().x > 550) //switch direction to left if too far right
		direction = left;
	if (view.getCenter().x - x > 480) //switch direction to right if too far left
		direction = right;


	if (planeType == mig51s)
		enemyBox.setPosition(x - 65, y - 115);
	else if (planeType == su37k)
		enemyBox.setPosition(x - 73, y - 125);
	else if (planeType == mig51)
		enemyBox.setPosition(x - 70, y - 152);

	loopPlaneBack(view);
}

void EnemyPlanes::loopPlaneBack(sf::View& view)
{
	if (y - view.getCenter().y > 700 && alive == true)
	{
		y = (float)view.getCenter().y - 500; //set new y coord
		x = (float)(rand() % 900 + 100); //set new x coord

		moveType = rand() % 2; //chance to change moving type
	}
}