#ifndef ENEMY_BELT
#define ENEMY_BELT

class EnemyBelt {
public:
	EnemyBelt() = default;
	//Get width from enemy sprite texture when loading
	EnemyBelt(int xPos1, int yPos1, int xPos2, int yPos2, int width);

	int getXPos1();
	int getYPos1();
	int getXPos2();
	int getYPos2();


private:

	int width;
	int xPos1;
	int yPos1;
	int xPos2;
	int yPos2;


};

#endif