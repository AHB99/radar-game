#pragma once
#include <utility>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>


#include "RTexture.h"
#include "rconfigurations.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "EnemyBelt.h"
#include "Radar.h"


bool initializeSDL(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer);
bool loadSprites(std::vector<RTexture>& allSprites, TTF_Font*& mainFont, TTF_Font*& gameOverFont, SDL_Renderer*& mainRenderer);
void closeAllSystems(SDL_Window*& mainWindow, SDL_Renderer*& mainRenderer, std::vector<RTexture>& allSprites, TTF_Font*& mainFont, TTF_Font*& gameOverFont);
void loadGameOverTexture(RTexture& gameOverTexture, TTF_Font*& gameOverFont, SDL_Renderer*& destinationRenderer);
void loadFinalPointsTexture(RTexture& finalPointsTexture, TTF_Font*& mainFont, SDL_Renderer*& destinationRenderer, int finalPoints);
void renderGameOverWithPoints(RTexture& gameOverTexture, RTexture& finalPointsTexture, SDL_Renderer*& destinationRenderer);


int generateUniformIntegerRandomNumberInRange(int start, int end);

bool generateRandomBool();

std::pair<int, int> getCenteredCoordinates(int textureWidth, int textureHeight, int screenWidth, int screenHeight);