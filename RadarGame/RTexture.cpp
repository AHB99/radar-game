#include "RTexture.h"

void RTexture::deallocateTexture() {
	if (rTexture != nullptr)
	{
		SDL_DestroyTexture(rTexture);
		rTexture = nullptr;
		rWidth = 0;
		rHeight = 0;
	}
}
