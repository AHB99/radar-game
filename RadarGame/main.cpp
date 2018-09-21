#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "RTexture.h"
#include "rconfigurations.h"
#include "Player.h"
#include "Coin.h"

using std::cout;
using std::cin;
using std::endl;


bool initializeSDL(SDL_Window*& mainWindow,SDL_Renderer*& mainRenderer);
bool loadSprites(std::vector<RTexture>& allSprites, SDL_Renderer*& mainRenderer);
void closeAllSystems(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer, std::vector<RTexture>& allSprites);
void handleCollisions(Player* mainPlayer, Coin* mainCoin);

int main(int argc, char* args[])
{
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* mainRenderer = nullptr;

	std::vector<RTexture> allSprites(3);

	if (!initializeSDL(mainWindow,mainRenderer))
	{
		cout << "Initialization failed" << endl;
	}
	else
	{
		if (!loadSprites(allSprites,mainRenderer))
		{
			cout << "Error: " << SDL_GetError();
		}	
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Main Player
			Player mainPlayer(&allSprites[rconfigurations::PLAYER_SPRITE]);
			Coin mainCoin(&allSprites[rconfigurations::COIN_SPRITE], rconfigurations::SCREEN_WIDTH/2,rconfigurations::SCREEN_HEIGHT/2);
		
			while (!quit)
			{
				//Event queue
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}	

					//Player key motions
					mainPlayer.changeVelocityFromKeys(e);
				}
				//Reflect changes to player position
				mainPlayer.moveUsingVelocity();
				handleCollisions(&mainPlayer, &mainCoin);
				
				//Clear screen
				SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(mainRenderer);

				mainPlayer.renderToScreen(mainRenderer);
				mainCoin.renderToScreen(mainRenderer);

				SDL_RenderPresent(mainRenderer);
			}
		}
	}

	closeAllSystems(mainWindow,mainRenderer, allSprites);

	return 0;
}

bool initializeSDL(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer)
{
	bool initialized = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL initialization failed. Errors:\n" << SDL_GetError << endl;
		initialized = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Linear texture filtering failed" << endl;
		}

		mainWindow = SDL_CreateWindow("Radar Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rconfigurations::SCREEN_WIDTH, rconfigurations::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mainWindow == nullptr)
		{
			cout << "Window creation failed. Errors:\n" << SDL_GetError << endl;
			initialized = false;
		}
		else
		{
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mainRenderer == nullptr)
			{
				cout << "Renderer creation failed. Errors:\n" << SDL_GetError << endl;
				initialized = false;
			}
			else
			{
				SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_Image initialization failed. Errors:\n" << IMG_GetError() << endl;
					initialized = false;
				}
			}
		}
	}

	return initialized;
}

bool loadSprites(std::vector<RTexture>& allSprites, SDL_Renderer*& mainRenderer) {
	bool noErrors = false;

	noErrors =  allSprites[rconfigurations::PLAYER_SPRITE].loadImageFromFile(rconfigurations::PLAYER_IMAGE_FILE, mainRenderer);
	noErrors = allSprites[rconfigurations::COIN_SPRITE].loadImageFromFile(rconfigurations::COIN_IMAGE_FILE, mainRenderer);
	noErrors = allSprites[rconfigurations::ENEMY_SPRITE].loadImageFromFile(rconfigurations::ENEMY_IMAGE_FILE, mainRenderer);


	return noErrors;
}


void closeAllSystems(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer, std::vector<RTexture>& allSprites) {

	for (auto texture : allSprites) {
		texture.deallocateTexture();
	}

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	mainWindow = nullptr;
	mainRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}

void handleCollisions(Player* mainPlayer, Coin* mainCoin) {
	if (isCollidingCircular(mainPlayer, mainCoin)) {
		//test teleportation for now
		if (mainCoin->getXPos() == rconfigurations::SCREEN_WIDTH / 2) {
			mainCoin->moveCoin(rconfigurations::SCREEN_WIDTH / 3, mainCoin->getYPos());
		}
		else {
			mainCoin->moveCoin(rconfigurations::SCREEN_WIDTH / 2, mainCoin->getYPos());

		}
	}
}
