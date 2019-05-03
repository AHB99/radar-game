#include "UtilityFunctions.h"
#include <random>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

int generateUniformIntegerRandomNumberInRange(int start, int end) {
	 static std::default_random_engine rawEngine( time(0) );
	 std::uniform_int_distribution<int> uniIntDist{ start,end };
	 return uniIntDist(rawEngine);
}

bool generateRandomBool() {
	static std::default_random_engine rawEngine(time(0));
	std::bernoulli_distribution bernDist{};
	return bernDist(rawEngine);
}

std::pair<int, int> getCenteredCoordinates(int textureWidth, int textureHeight, int screenWidth, int screenHeight) {
	std::pair<int, int> result;
	result.first = (screenWidth / 2) - (textureWidth / 2);
	result.second = (screenHeight / 2) - (textureHeight / 2);
	return result;
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

				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! " << TTF_GetError() << endl;
					initialized = false;
				}

			}
		}
	}

	return initialized;

}

bool loadSprites(std::vector<RTexture>& allSprites, TTF_Font*& mainFont, TTF_Font*& gameOverFont, SDL_Renderer*& mainRenderer) {
	bool noErrors = false;

	noErrors = allSprites[rconfigurations::PLAYER_SPRITE].loadImageFromFile(rconfigurations::PLAYER_IMAGE_FILE, mainRenderer);
	noErrors = allSprites[rconfigurations::COIN_SPRITE].loadImageFromFile(rconfigurations::COIN_IMAGE_FILE, mainRenderer);
	noErrors = allSprites[rconfigurations::ENEMY_SPRITE].loadImageFromFile(rconfigurations::ENEMY_IMAGE_FILE, mainRenderer);
	noErrors = allSprites[rconfigurations::RADAR_SPRITE].loadImageFromFile(rconfigurations::RADAR_IMAGE_FILE, mainRenderer);

	mainFont = TTF_OpenFont(rconfigurations::FONT_FILE.c_str(), 15);
	if (mainFont == nullptr) {
		cout << "Couldn't open main font file " << TTF_GetError() << endl;
		noErrors = false;
	}

	gameOverFont = TTF_OpenFont(rconfigurations::GAME_OVER_FONT_FILE.c_str(), 40);
	if (gameOverFont == nullptr) {
		cout << "Couldn't open game over font file " << TTF_GetError() << endl;
		noErrors = false;
	}

	return noErrors;
}


void closeAllSystems(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer, std::vector<RTexture>& allSprites, TTF_Font*& mainFont, TTF_Font*& gameOverFont) {

	for (auto texture : allSprites) {
		texture.deallocateTexture();
	}
	TTF_CloseFont(mainFont);
	mainFont = nullptr;
	TTF_CloseFont(gameOverFont);
	gameOverFont = nullptr;

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	mainWindow = nullptr;
	mainRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void loadGameOverTexture(RTexture& gameOverTexture, TTF_Font*& gameOverFont, SDL_Renderer*& destinationRenderer) {
	gameOverTexture.loadBlendedTextFromFont(destinationRenderer, "Game Over", { 255,0,0 }, gameOverFont);
}

void loadFinalPointsTexture(RTexture& finalPointsTexture, TTF_Font*& mainFont, SDL_Renderer*& destinationRenderer, int finalPoints) {
	finalPointsTexture.loadBlendedTextFromFont(destinationRenderer, "Points: " + std::to_string(finalPoints), { 0,0,0 }, mainFont);
}

void renderGameOverWithPoints(RTexture& gameOverTexture, RTexture& finalPointsTexture, SDL_Renderer*& destinationRenderer) {
	std::pair<int, int> gameOverCenteredCoordinates{ getCenteredCoordinates(gameOverTexture.getWidth(), gameOverTexture.getHeight(), rconfigurations::SCREEN_WIDTH, rconfigurations::SCREEN_HEIGHT) };
	gameOverTexture.renderCurrentTexture(gameOverCenteredCoordinates.first, gameOverCenteredCoordinates.second, destinationRenderer);

	std::pair<int, int> finalPointsCenteredCoordinates{ getCenteredCoordinates(finalPointsTexture.getWidth(), finalPointsTexture.getHeight(), rconfigurations::SCREEN_WIDTH, rconfigurations::SCREEN_HEIGHT) };
	//To prevent overlap
	finalPointsCenteredCoordinates.second += gameOverTexture.getHeight();
	finalPointsTexture.renderCurrentTexture(finalPointsCenteredCoordinates.first, finalPointsCenteredCoordinates.second, destinationRenderer);
}


