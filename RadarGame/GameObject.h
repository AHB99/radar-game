#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SDL.h>
#include <SDL_image.h>
#include "RTexture.h"

class GameObject {
public:

	GameObject() = default;
	GameObject(RTexture* gameObjectTexture, int xPos = 0, int yPos = 0);
	
	bool renderToScreen(SDL_Renderer*& destinationRenderer);


	virtual ~GameObject() = default;

protected:
	RTexture* gameObjectTexture = nullptr;

	int xPos = 0;
	int yPos = 0;
};

#endif