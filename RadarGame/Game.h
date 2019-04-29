#ifndef  GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include "RTexture.h"
#include "Enemy.h"
#include "EnemyBelt.h"
#include "Player.h"
#include "Coin.h"
#include "Radar.h"
#include "rconfigurations.h"
#include "UtilityFunctions.h"

//Time delay for slowing down the radar
const int RADAR_SPEED_TIMER = 5000;

//Max delay between radar blinks before game is unplayable
const int MAX_RADAR_SPEED = 10000;
//Min delay between radar blinks before game is unplayable
const int MIN_RADAR_SPEED = 2000;

//Debug change to 200
const int RADAR_SPEED_DELTA = 500;


class Game {
public:
	Game();
	Game(RTexture* playerTexture, RTexture* coinTexture, int coinXPos, int coinYPos, RTexture* radarTexture);
	void setUpEnemyBelts(std::vector<RTexture>& allSprites);
	void setUpEnemies(std::vector<RTexture>& allSprites);
	void changePlayerVelocityByKeys(SDL_Event& e);
	void movePlayerUsingVelocity();
	void accelerateEnemies(Uint32 currTime);
	void moveAllEnemies();
	void handleCollisions();
	void randomizeCoinLocation();
	void renderGameObjects(SDL_Renderer*& destinationRenderer);
	void renderRadar(SDL_Renderer*& destinationRenderer);
	void executeRadar();
	void slowDownRadar();
	void setGameOver() {
		quitGame = true;
	}
	bool isGameOver() {
		return quitGame;
	}

private:
	//Private member functions
	//Increases frequency of radar blinks, till the limit
	void speedUpRadar();


	//Private member variables
	Player gamePlayer;
	Coin gameCoin;
	Radar gameRadar;
	std::vector<EnemyBelt> gameEnemyBelts;
	std::vector<Enemy> gameEnemies;
	int gamePoints = 0;
	int radarSpeed = MIN_RADAR_SPEED;
	bool quitGame = false;

	//Time stamp for last time radar was slowed down
	Uint32 slowDownRadarLastTime = 0;
	//Time stamp for last time radar was blinked
	Uint32 blinkRadarLastTime = 0;

};

#endif

