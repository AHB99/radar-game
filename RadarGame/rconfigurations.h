#ifndef RCONFIGURATIONS
#define RCONFIGURATIONS

#include <string>

namespace rconfigurations {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const std::string PLAYER_IMAGE_FILE = "playerSprite.png";
	const std::string COIN_IMAGE_FILE = "coinSprite.png";
	const std::string ENEMY_IMAGE_FILE = "enemySprite.png";
	const std::string RADAR_IMAGE_FILE = "radarSprite.png";
	const std::string FONT_FILE = "SourceCodePro-Regular.otf";



	enum spriteIndicies {
		PLAYER_SPRITE = 0,
		COIN_SPRITE = 1,
		ENEMY_SPRITE = 2,
		RADAR_SPRITE = 3
	};
}


#endif

