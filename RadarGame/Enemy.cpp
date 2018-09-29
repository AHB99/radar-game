#include "Enemy.h"

Enemy::Enemy(RTexture* enemyTexture, bool verticalOrientation):
	GameObject(enemyTexture), enemySpeedDelta(5), velocity(5), verticalOrientation(verticalOrientation) { }

void Enemy::moveToRoam() {
	
	//Later will have changing velocities here
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


