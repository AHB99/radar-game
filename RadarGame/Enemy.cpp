#include "Enemy.h"
#include "UtilityFunctions.h"
#include <utility>

Enemy::Enemy(RTexture* enemyTexture, bool verticalOrientation, int xPos, int yPos):
	GameObject(enemyTexture, xPos, yPos), enemySpeedDelta(VEL_INIT), velocity(VEL_INIT), verticalOrientation(verticalOrientation) { }

void Enemy::moveToRoam() {
	
	if (velocity > 0) {
		velocity = enemySpeedDelta;
	}
	else {
		velocity = -1 * enemySpeedDelta;
	}

	if (verticalOrientation) {
		yPos += velocity;
	}
	else {
		xPos += velocity;
	}

	if (!verticalOrientation&&((xPos < 0) || (xPos + gameObjectTexture->getWidth() > rconfigurations::SCREEN_WIDTH)))
	{
		xPos -= velocity;
		velocity *= -1;
	} else if (verticalOrientation&&((yPos < 0) || (yPos + gameObjectTexture->getHeight() > rconfigurations::SCREEN_HEIGHT)))
	{
		yPos -= velocity;
		velocity *= -1;

	}
}

Enemy::Enemy(RTexture* enemyTexture, EnemyBelt& linkedEnemyBelt) : GameObject(enemyTexture), enemySpeedDelta(VEL_INIT), velocity(VEL_INIT), verticalOrientation(linkedEnemyBelt.isVertical()) {
	//Spawn the enemy on the belt, in a random displacement along it.
	std::pair<int, int> randomCoords{ linkedEnemyBelt.getRandomCoordinatesOnBelt(enemyTexture->getHeight(), enemyTexture->getWidth()) };
	xPos = randomCoords.first;
	yPos = randomCoords.second;
	//Randomize initial direction
	if (generateRandomBool()) {
		velocity *= -1;
	}
}

void Enemy::accelarate(Uint32 currTime) {
	if ((currTime > 5000)&&(enemySpeedDelta != VEL_MAX)) {
		int currentTimeSpeedCalc = log(currTime);
		enemySpeedDelta += currentTimeSpeedCalc - lastTimeSpeedCalc;
		lastTimeSpeedCalc = currentTimeSpeedCalc;
		
	}
}

