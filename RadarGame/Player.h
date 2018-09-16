#ifndef PLAYER
#define PLAYER

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "RTexture.h"
#include "GameObject.h"
#include "rconfigurations.h"

class Player : public GameObject {
public:

	Player() = default;
	Player(RTexture* playerTexture, int xPos = 0, int yPos = 0);

	//Pixel size of sprite
	//sync's with image/texture
	static const int PLAYER_WIDTH = 20;
	static const int PLAYER_HEIGHT = 20;

	//Change in velocity upon keypress
	static const int PLAYER_VEL_DELTA = 5;

	void moveUsingVelocity();

	void changeVelocityFromKeys(SDL_Event& e);

	

private:
	

	int xVel = 0;
	int yVel = 0;
};

#endif