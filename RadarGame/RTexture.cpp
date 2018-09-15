#include "RTexture.h"

using std::cout;


void RTexture::deallocateTexture() {
	if (rTexture != nullptr)
	{
		SDL_DestroyTexture(rTexture);
		rTexture = nullptr;
		rWidth = 0;
		rHeight = 0;
	}
}

bool RTexture::loadImageFromFile(std::string fileName, SDL_Renderer*& destinationRenderer)
{
	deallocateTexture();

	SDL_Texture* resultTexture = NULL;

	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
	if (tempSurface == NULL)
	{
		cout << "Failed to load image to surface:" << fileName << IMG_GetError();
	}
	else
	{
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

		resultTexture = SDL_CreateTextureFromSurface(destinationRenderer, tempSurface);
		if (resultTexture == nullptr)
		{
			cout << "Failed to load image to texture:" << fileName << SDL_GetError();
		}
		else
		{
			rWidth = tempSurface->w;
			rHeight = tempSurface->h;
		}

		SDL_FreeSurface(tempSurface);
	}

	rTexture = resultTexture;
	return (rTexture != nullptr);
}

bool RTexture::renderCurrentTexture(int x, int y, SDL_Renderer*& destinationRenderer) {
	SDL_Rect destinationRect = { x, y, rWidth, rHeight };

	return (!SDL_RenderCopy(destinationRenderer, rTexture,NULL,&destinationRect));
}




