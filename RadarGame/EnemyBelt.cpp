#include "EnemyBelt.h"


EnemyBelt::EnemyBelt(int xPos1, int yPos1, int xPos2, int yPos2, int width) : 
	width(width), xPos1(xPos1), yPos1(yPos1), xPos2(xPos2), yPos2(xPos2) { }

int EnemyBelt::getXPos1() {
	return xPos1;
}
int EnemyBelt::getYPos1() {
	return yPos1;
}
int EnemyBelt::getXPos2() {
	return xPos2;
}
int EnemyBelt::getYPos2() {
	return yPos2;
}