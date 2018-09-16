#include "GameObject.h"

GameObject::GameObject(RTexture* gameObjectTexture, int xPos, int yPos)
	: gameObjectTexture(gameObjectTexture), xPos(xPos),yPos(yPos) { }

bool GameObject::renderToScreen(SDL_Renderer*& destinationRenderer) {
	return gameObjectTexture->renderCurrentTexture(xPos, yPos, destinationRenderer);
}

