#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "RTexture.h"
#include "rconfigurations.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "EnemyBelt.h"
#include "Radar.h"
#include "UtilityFunctions.h"

#include "Game.h"

using std::cout;
using std::cin;
using std::endl;


bool initializeSDL(SDL_Window*& mainWindow,SDL_Renderer*& mainRenderer);
bool loadSprites(std::vector<RTexture>& allSprites, SDL_Renderer*& mainRenderer);
void closeAllSystems(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer, std::vector<RTexture>& allSprites);

int main(int argc, char* args[])
{


	
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* mainRenderer = nullptr;

	std::vector<RTexture> allSprites(4);
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
			//Begin game
			Game mainGame(&allSprites[rconfigurations::PLAYER_SPRITE], &allSprites[rconfigurations::COIN_SPRITE], rconfigurations::SCREEN_WIDTH / 2, rconfigurations::SCREEN_HEIGHT / 2, &allSprites[rconfigurations::RADAR_SPRITE]);

			//Event handler
			SDL_Event e;

			mainGame.setUpEnemyBelts(allSprites);
			mainGame.setUpEnemies(allSprites);
			mainGame.randomizeCoinLocation();

			//Game Loop
			while (!mainGame.isGameOver()) {
				//Event queue
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						mainGame.setGameOver();
					}	

					//Player key motions
					mainGame.changePlayerVelocityByKeys(e);
				}
				//Reflect changes to player position
				mainGame.movePlayerUsingVelocity();

				mainGame.accelerateEnemies(SDL_GetTicks());
				mainGame.moveAllEnemies();

				mainGame.handleCollisions();
				
				//Clear screen with background color
				SDL_SetRenderDrawColor(mainRenderer, 0xaa, 0xaa, 0xa0, 0xFF);
				SDL_RenderClear(mainRenderer);

				mainGame.renderGameObjects(mainRenderer);

				mainGame.slowDownRadar();
				mainGame.executeRadar();
				//mainGame.renderRadar(mainRenderer);

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
	noErrors = allSprites[rconfigurations::RADAR_SPRITE].loadImageFromFile(rconfigurations::RADAR_IMAGE_FILE, mainRenderer);


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

