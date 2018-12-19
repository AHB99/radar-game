#ifndef RADAR
#define RADAR

#include <SDL.h>
#include <SDL_image.h>
#include "RTexture.h"
#include "rconfigurations.h"

class Radar {
public:
	Radar() = default;
	Radar(RTexture* radTexture);
	void setAlpha(Uint8 alpha);
	bool renderToScreen(SDL_Renderer*& destinationRenderer);


private:
	RTexture* radarTexture = nullptr;
};
#endif 
