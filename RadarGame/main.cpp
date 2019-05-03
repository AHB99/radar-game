#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

int main(int argc, char* args[])
{
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* mainRenderer = nullptr;
	std::vector<RTexture> allSprites(4);
	TTF_Font* mainFont = nullptr;
	TTF_Font* gameOverFont = nullptr;

	if (!initializeSDL(mainWindow,mainRenderer))
	{
		cout << "Initialization failed" << endl;
	}
	else
	{
		if (!loadSprites(allSprites,mainFont, gameOverFont, mainRenderer))
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
			mainGame.loadScoreTexture(mainFont, mainRenderer);

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

				mainGame.handleCollisions(mainFont, mainRenderer);
				
				//Clear screen with background color
				SDL_SetRenderDrawColor(mainRenderer, 0xaa, 0xaa, 0xa0, 0xFF);
				SDL_RenderClear(mainRenderer);

				mainGame.renderGameObjects(mainRenderer);

				mainGame.slowDownRadar();
				mainGame.executeRadar();
				mainGame.renderRadar(mainRenderer);

				mainGame.renderScore(mainRenderer);

				SDL_RenderPresent(mainRenderer);
			}

			//Game Over Phase
			bool freezeScreen = true;
			SDL_Event eventForUserQuitting;
			RTexture gameOverTexture, finalPointsTexture;
			
			loadGameOverTexture(gameOverTexture, gameOverFont, mainRenderer);
			loadFinalPointsTexture(finalPointsTexture, mainFont, mainRenderer, mainGame.getScore());

			//Only display game objects so player can see how they died
			SDL_SetRenderDrawColor(mainRenderer, 0xaa, 0xaa, 0xa0, 0xFF);
			SDL_RenderClear(mainRenderer);
			mainGame.renderGameObjects(mainRenderer);
			renderGameOverWithPoints(gameOverTexture, finalPointsTexture, mainRenderer);
			SDL_RenderPresent(mainRenderer);

			while (freezeScreen) {
				while (SDL_PollEvent(&eventForUserQuitting) != 0) {
					if (eventForUserQuitting.type == SDL_QUIT) {
						freezeScreen = false;
					}
				}
			}

		}
	}

	closeAllSystems(mainWindow,mainRenderer, allSprites, mainFont, gameOverFont);
	
	return 0;
	
}


