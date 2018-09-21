#include "Enemy.h"

Enemy::Enemy(RTexture* enemyTexture, bool verticalOrientation, bool positiveDirection):
	GameObject(enemyTexture), enemySpeedDelta(5), velocity(5), verticalOrientation(verticalOrientation), positiveDirection(positiveDirection){ }

void Enemy::moveToRoam() {
	
	if (positiveDirection) {
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
		positiveDirection = !positiveDirection;
	} else if (verticalOrientation&&((yPos < 0) || (yPos + gameObjectTexture->getHeight() > rconfigurations::SCREEN_HEIGHT)))
	{
		yPos -= velocity;
		positiveDirection = !positiveDirection;

	}
}


