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

class Game {
public:
	Game();
	Game(RTexture* playerTexture, RTexture* coinTexture, int coinXPos, int coinYPos, RTexture* radarTexture);
	void setUpEnemyBelts();
	void setUpEnemies(std::vector<RTexture>& allSprites);
	void changePlayerVelocityByKeys(SDL_Event& e);
	void movePlayerUsingVelocity();
	void accelerateEnemies(Uint32 currTime);
	void moveAllEnemies();
	void handleCollisions();
	void renderGameObjects(SDL_Renderer*& destinationRenderer);
	void renderRadar(SDL_Renderer*& destinationRenderer);
	void executeRadar();
	void setGameOver() {
		quitGame = true;
	}
	bool isGameOver() {
		return quitGame;
	}

private:
	Player gamePlayer;
	Coin gameCoin;
	Radar gameRadar;
	std::vector<EnemyBelt> gameEnemyBelts;
	std::vector<Enemy> gameEnemies;
	int gamePoints = 0;
	bool quitGame = false;
};

#endif // ! GAME_H

