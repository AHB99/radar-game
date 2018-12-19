#ifndef ENEMY_BELT
#define ENEMY_BELT

class EnemyBelt {
public:
	EnemyBelt() = default;
	//Get width from enemy sprite texture when loading
	EnemyBelt(bool verticalOrientation, int position = 0);
	bool getOrientation() const;
	int getPosition() const;


private:

	bool verticalOrientation;

	//Offset position from zero, relates to X or Y depending on orientation
	int position;

};

#endif