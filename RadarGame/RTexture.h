#ifndef RTEXTURE
#define RTEXTURE

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "rconfigurations.h"

class RTexture {
public:
	RTexture() : rTexture(nullptr) {}
	~RTexture() { deallocateTexture(); }

	bool loadImageFromFile(std::string fileName, SDL_Renderer*& destinationRenderer);

	bool renderCurrentTexture(int x, int y, SDL_Renderer*& destinationRenderer);
	bool renderCurrentTextureToFullScreen(int x, int y, SDL_Renderer*& destinationRenderer);

	
	void setAlpha(Uint8 alpha);
	void setBlendMode();


	void deallocateTexture();

	int getWidth();
	int getHeight();

private:

	SDL_Texture* rTexture;

	int rWidth = 0;
	int rHeight = 0;


};

#endif
