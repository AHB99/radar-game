#ifndef RTEXTURE
#define RTEXTURE

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

class RTexture {
public:
	RTexture() : rTexture(nullptr) {}
	~RTexture() { deallocateTexture(); }

	bool loadImageFromFile(std::string fileName, SDL_Renderer*& destinationRenderer);
	bool renderCurrentTexture(int x, int y, SDL_Renderer*& destinationRenderer);

	void deallocateTexture();


private:

	SDL_Texture* rTexture;

	int rWidth = 0;
	int rHeight = 0;


};

#endif
