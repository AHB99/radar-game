#ifndef ENEMY_BELT
#define ENEMY_BELT

#include <utility>

class EnemyBelt {
public:
	EnemyBelt() = default;
	//Get width from enemy sprite texture when loading
	EnemyBelt(bool verticalOrientation, int position = 0);
	bool isVertical() const;
	int getPosition() const;
	std::pair<int,int> getRandomCoordinatesOnBelt(int gameObjectHeight, int gameObjectWidth) const;


private:

	bool verticalOrientation;

	//Offset position from zero, relates to X or Y depending on orientation
	int position;

};

#endif