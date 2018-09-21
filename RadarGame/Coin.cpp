#include "Coin.h"

Coin::Coin(RTexture* playerTexture, int xPos, int yPos) :
	GameObject(playerTexture, xPos, yPos) { }

void Coin::moveCoin(int newXPosition, int newYPosition){
	xPos = newXPosition;
	yPos = newYPosition;	
}
