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
		//Coin collection speeds up the radar (to a limit)
		speedUpRadar();

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

	int currentTime = SDL_GetTicks() % radarSpeed;
	if (((currentTime >= 0) && (currentTime <= 200)) && (!gameRadar.isBlinking())) {
		gameRadar.startBlink();
	}
	gameRadar.updateBlink();
}

void Game::slowDownRadar() {
	Uint32 currentTime = SDL_GetTicks();
	//If the time elapsed since last slowDown update is more than the fixed RadarSpeedTimer value, and the radar speed is less than the fixed MaximumRadarSpeed, slow down the radar
	if (((currentTime-slowDownRadarLastTime) > RADAR_SPEED_TIMER) && (radarSpeed < MAX_RADAR_SPEED)) {
		radarSpeed += RADAR_SPEED_DELTA;
		slowDownRadarLastTime = currentTime;
	}
}

void Game::speedUpRadar() {
	int newRadarSpeed = radarSpeed - RADAR_SPEED_DELTA;
	//Only reduce delay if above fixed MinimumRadarSpeed, else set it to the fixed MinimumRadarSpeed
	if (newRadarSpeed >= MIN_RADAR_SPEED) {
		radarSpeed = newRadarSpeed;
	}
	else {
		radarSpeed = MIN_RADAR_SPEED;
	}
}

