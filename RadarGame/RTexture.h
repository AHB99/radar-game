#ifndef RTEXTURE
#define RTEXTURE

#include <SDL.h>
#include <SDL_image.h>

class RTexture {
public:
	RTexture() : rTexture(nullptr) {}
	~RTexture() { deallocateTexture(); }

	void deallocateTexture();


private:

	SDL_Texture* rTexture;

	int rWidth = 0;
	int rHeight = 0;


};

#endif
