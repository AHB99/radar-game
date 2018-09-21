#ifndef ENEMY
#define ENEMY

#include "GameObject.h"
#include "rconfigurations.h"

class RTexture;

class Enemy : public GameObject {
public:
	Enemy() = default;
	Enemy(RTexture* enemyTexture, bool verticalOrientation);

	void moveUsingVelocity();
	void changeVelocityToRoam(int upperBound, int lowerBound);

private:
	int enemySpeedDelta;
	int velocity;
	bool verticalOrientation;
	bool positiveDirection;


};

#endif
