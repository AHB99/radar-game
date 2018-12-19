#include "GameObject.h"

GameObject::GameObject(RTexture* gameObjectTexture, int xPos, int yPos)
	: gameObjectTexture(gameObjectTexture), xPos(xPos),yPos(yPos) { }

bool GameObject::renderToScreen(SDL_Renderer*& destinationRenderer) {
	return gameObjectTexture->renderCurrentTexture(xPos, yPos, destinationRenderer);
}

int GameObject::getWidth() {
	return gameObjectTexture->getWidth();
}
int GameObject::getHeight() {
	return gameObjectTexture->getHeight();
}

int GameObject::getXPos() {
	return xPos;
}
int GameObject::getYPos() {
	return yPos;
}

bool isCollidingCircular(GameObject& lhs, GameObject& rhs) {
	double lhsRadius = lhs.getWidth() / 2.0;
	double rhsRadius = rhs.getWidth() / 2.0;

	double lhsCenterXPos = lhs.getXPos() + lhsRadius;
	double lhsCenterYPos = lhs.getYPos() + lhsRadius;
	double rhsCenterXPos = rhs.getXPos() + rhsRadius;
	double rhsCenterYPos = rhs.getYPos() + rhsRadius;

	double distanceBetweenCentersSquared = pow((lhsCenterXPos - rhsCenterXPos), 2) + pow((lhsCenterYPos - rhsCenterYPos), 2);

	return (distanceBetweenCentersSquared<(pow(lhsRadius+rhsRadius,2)));
}



