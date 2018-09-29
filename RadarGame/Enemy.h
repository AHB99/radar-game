#ifndef ENEMY
#define ENEMY

#include "GameObject.h"
#include "rconfigurations.h"

class RTexture;

class Enemy : public GameObject {
public:
	Enemy() = default;
	Enemy(RTexture* enemyTexture, bool verticalOrientation);

	void moveToRoam();

private:
	int enemySpeedDelta;
	int velocity;

	bool verticalOrientation;

};

#endif
