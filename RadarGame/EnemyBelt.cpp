#include "EnemyBelt.h"


EnemyBelt::EnemyBelt(bool verticalOrientation, int position) :
	verticalOrientation(verticalOrientation), position(position) { }

bool EnemyBelt::getOrientation() const {
	return verticalOrientation;
}
int EnemyBelt::getPosition() const {
	return position;
}