#ifndef ENEMY
#define ENEMY

#include "GameObject.h"
#include "EnemyBelt.h"
#include "rconfigurations.h"
#include <cmath>
#include <iostream>

const int VEL_INIT = 3;
const int VEL_MAX = 50;

class RTexture;
class EnemyBelt;
class Enemy : public GameObject {
public:
	Enemy() = default;
	Enemy(RTexture* enemyTexture, bool verticalOrientation, int xPos = 0, int yPos = 0);
	Enemy(RTexture* enemyTexture, EnemyBelt& linkedEnemyBelt);


	void moveToRoam();
	void accelarate(Uint32 currTime);

private:
	int enemySpeedDelta;
	int velocity;
	int lastTimeSpeedCalc = 8;

	bool verticalOrientation;

};

#endif
