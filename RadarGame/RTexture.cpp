#include "RTexture.h"

using std::cout;
using std::endl;


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

bool RTexture::loadTextFromFont(SDL_Renderer*& destinationRenderer, std::string writtenText, SDL_Color textColor, TTF_Font* givenFont) {
		deallocateTexture();
		SDL_Surface* textSurface = TTF_RenderText_Solid(givenFont, writtenText.c_str(), textColor);

		if (textSurface == NULL)
		{
			cout << "Failed to load text: " << TTF_GetError() << endl;
		}
		else
		{
			rTexture = SDL_CreateTextureFromSurface(destinationRenderer, textSurface);
			if (rTexture == NULL)
			{
				cout << "Failed to load texture for text: " << SDL_GetError() << endl;
			}
			else
			{
				rWidth = textSurface->w;
				rHeight = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}

		//Return success
		return rTexture != NULL;

}

bool RTexture::renderCurrentTexture(int x, int y, SDL_Renderer*& destinationRenderer) {
	SDL_Rect destinationRect = { x, y, rWidth, rHeight };

	return (!SDL_RenderCopy(destinationRenderer, rTexture,NULL,&destinationRect));
}

bool RTexture::renderCurrentTextureToFullScreen(int x, int y, SDL_Renderer*& destinationRenderer) {

	return (!SDL_RenderCopy(destinationRenderer, rTexture, NULL, NULL));
}


int RTexture::getWidth() {
	return rWidth;
}
int RTexture::getHeight() {
	return rHeight;
}




void RTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(rTexture, alpha);
}

void RTexture::setBlendMode() {
	SDL_SetTextureBlendMode(rTexture, SDL_BLENDMODE_BLEND);
}




