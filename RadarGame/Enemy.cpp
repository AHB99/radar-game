#include "Enemy.h"

Enemy::Enemy(RTexture* enemyTexture, bool verticalOrientation):
	GameObject(enemyTexture), enemySpeedDelta(5), velocity(5), verticalOrientation(verticalOrientation) { }

void Enemy::moveUsingVelocity() {
	if (verticalOrientation) {
		yPos += velocity;
	}
	else {
		xPos += velocity;
	}

	if (!verticalOrientation&&((xPos < 0) || (xPos + gameObjectTexture->getWidth() > rconfigurations::SCREEN_WIDTH)))
	{
		xPos -= velocity;
	} else if (verticalOrientation&&((yPos < 0) || (yPos + gameObjectTexture->getHeight() > rconfigurations::SCREEN_HEIGHT)))
	{
		yPos -= velocity;
	}
}

void Enemy::changeVelocityToRoam(int upperBound, int lowerBound) {
}

