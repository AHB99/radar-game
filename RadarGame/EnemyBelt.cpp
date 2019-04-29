#include "EnemyBelt.h"
#include "UtilityFunctions.h"
#include "rconfigurations.h"


EnemyBelt::EnemyBelt(bool verticalOrientation, int position) :
	verticalOrientation(verticalOrientation), position(position) { }

bool EnemyBelt::isVertical() const {
	return verticalOrientation;
}
int EnemyBelt::getPosition() const {
	return position;
}

std::pair<int,int> EnemyBelt::getRandomCoordinatesOnBelt(int gameObjectHeight, int gameObjectWidth) const {
	std::pair<int, int> result;
	if (verticalOrientation) {
		result.first = position;
		result.second = generateUniformIntegerRandomNumberInRange(0, rconfigurations::SCREEN_HEIGHT - gameObjectHeight);
	}
	else {
		result.first = generateUniformIntegerRandomNumberInRange(0, rconfigurations::SCREEN_WIDTH - gameObjectWidth);
		result.second = position;
	}
	return result;
}
