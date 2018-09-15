#ifndef PLAYER
#define PLAYER

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "RTexture.h"
#include "rconfigurations.h"

class Player {
public:

	Player() = default;

	//Pixel size of sprite
	static const int PLAYER_WIDTH = 20;
	static const int PLAYER_HEIGHT = 20;

	//Change in velocity upon keypress
	static const int PLAYER_VEL_DELTA = 10;

	bool loadSpriteFromFile(std::string fileName, SDL_Renderer*& destinationRenderer);

	void moveUsingVelocity();

	void changeVelocityFromKeys(SDL_Event& e);

	bool renderToScreen(SDL_Renderer*& destinationRenderer);
	

private:
	//TODO
	RTexture playerTexture;

	int xPos = 0;
	int yPos = 0;

	int xVel = 0;
	int yVel = 0;
};

#endif