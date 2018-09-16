#include "Player.h"

Player::Player(RTexture* playerTexture, int xPos, int yPos) :
	GameObject(playerTexture,xPos,yPos) { }


void Player::moveUsingVelocity() {
	xPos += xVel;

	if ((xPos < 0) || (xPos + PLAYER_WIDTH > rconfigurations::SCREEN_WIDTH))
	{
		xPos -= xVel;
	}

	yPos += yVel;

	if ((yPos < 0) || (yPos + PLAYER_HEIGHT > rconfigurations::SCREEN_HEIGHT))
	{
		yPos -= yVel;
	}
}


void Player::changeVelocityFromKeys(SDL_Event& e) {

	//Add velocity if key is down
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: yVel -= PLAYER_VEL_DELTA; break;
		case SDLK_DOWN: yVel += PLAYER_VEL_DELTA; break;
		case SDLK_LEFT: xVel -= PLAYER_VEL_DELTA; break;
		case SDLK_RIGHT: xVel += PLAYER_VEL_DELTA; break;
		}
	}

	//Remove velocity if key is up
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: yVel += PLAYER_VEL_DELTA; break;
		case SDLK_DOWN: yVel -= PLAYER_VEL_DELTA; break;
		case SDLK_LEFT: xVel += PLAYER_VEL_DELTA; break;
		case SDLK_RIGHT: xVel -= PLAYER_VEL_DELTA; break;
		}
	}

}
