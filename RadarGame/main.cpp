#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "RTexture.h"
#include "rconfigurations.h"
#include "Player.h"

using std::cout;
using std::cin;
using std::endl;


bool initializeSDL(SDL_Window*& mainWindow,SDL_Renderer*& mainRenderer);
void closeAllSystems(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer);

int main(int argc, char* args[])
{
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* mainRenderer = nullptr;

	Player mainPlayer;

	if (!initializeSDL(mainWindow,mainRenderer))
	{
		cout << "Initialization failed" << endl;
	}
	else
	{
		if (!mainPlayer.loadSpriteFromFile("testPlayer.png", mainRenderer))
		{
			cout << "Error: " << SDL_GetError();
		}	
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
		
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


				//Clear screen
				SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(mainRenderer);

				mainPlayer.renderToScreen(mainRenderer);

				SDL_RenderPresent(mainRenderer);
			}
		}
	}

	closeAllSystems(mainWindow,mainRenderer);

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

void closeAllSystems(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer) {

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	mainWindow = nullptr;
	mainRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}