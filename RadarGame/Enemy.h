#ifndef ENEMY
#define ENEMY

#include "GameObject.h"
#include "EnemyBelt.h"
#include "rconfigurations.h"

class RTexture;
class EnemyBelt;
class Enemy : public GameObject {
public:
	Enemy() = default;
	Enemy(RTexture* enemyTexture, bool verticalOrientation, int xPos = 0, int yPos = 0);
	Enemy(RTexture* enemyTexture, EnemyBelt& linkedEnemyBelt);


	void moveToRoam();

private:
	int enemySpeedDelta;
	int velocity;

	bool verticalOrientation;

};

#endif
