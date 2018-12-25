#include "Game.h"

Game::Game() { }

Game::Game(RTexture* playerTexture, RTexture* coinTexture, int coinXPos, int coinYPos, RTexture* radarTexture)
	: gamePlayer(playerTexture), gameCoin(coinTexture, coinXPos, coinYPos), gameRadar(radarTexture) {
}

void Game::setUpEnemyBelts() {
	gameEnemyBelts.push_back(EnemyBelt(true, rconfigurations::SCREEN_WIDTH / 3));
	gameEnemyBelts.push_back(EnemyBelt(true, 2 * (rconfigurations::SCREEN_WIDTH / 3)));
	gameEnemyBelts.push_back(EnemyBelt(false, (rconfigurations::SCREEN_HEIGHT / 2)));
}

void Game::setUpEnemies(std::vector<RTexture>& allSprites) {
	for (auto& enemyBelt : gameEnemyBelts) {
		gameEnemies.push_back(Enemy(&allSprites[rconfigurations::ENEMY_SPRITE], enemyBelt));
	}
}

void Game::changePlayerVelocityByKeys(SDL_Event& e) {
	gamePlayer.changeVelocityFromKeys(e);
}

void Game::movePlayerUsingVelocity() {
	gamePlayer.moveUsingVelocity();
}

void Game::accelerateEnemies(Uint32 currTime) {
	for (auto&enemy : gameEnemies) {
		enemy.accelarate(currTime);
	}
}

void Game::moveAllEnemies() {
	for (auto& enemy : gameEnemies) {
		enemy.moveToRoam();
	}
}

void Game::handleCollisions() {
	if (isCollidingCircular(gamePlayer, gameCoin)) {
		//test teleportation for now
		if (gameCoin.getXPos() == rconfigurations::SCREEN_WIDTH / 2) {
			gameCoin.moveCoin(rconfigurations::SCREEN_WIDTH / 3, gameCoin.getYPos());
		}
		else {
			gameCoin.moveCoin(rconfigurations::SCREEN_WIDTH / 2, gameCoin.getYPos());

		}
		gamePoints++;
		// DEBUG
		std::cout << "Points: " << gamePoints << std::endl;

		// END DEBUG
	}
	for (auto& enemy : gameEnemies) {
		if (isCollidingCircular(gamePlayer, enemy)) {
			// DEBUG keep quitting off
			//quitGame = true;
			std::cout << "Hit" << std::endl;
		}
	}
}

void Game::renderGameObjects(SDL_Renderer*& destinationRenderer) {
	gamePlayer.renderToScreen(destinationRenderer);
	gameCoin.renderToScreen(destinationRenderer);
	for (auto& enemy : gameEnemies) {
		enemy.renderToScreen(destinationRenderer);
	}
}

void Game::renderRadar(SDL_Renderer*& destinationRenderer) {
	gameRadar.renderToScreen(destinationRenderer);
}

void Game::executeRadar() {
	//2000-> radar speed, will decide later.
	int currentTime = SDL_GetTicks() % 2000;
	if (((currentTime >= 0) && (currentTime <= 200)) && (!gameRadar.isBlinking())) {
		gameRadar.startBlink();
	}
	gameRadar.updateBlink();
}

