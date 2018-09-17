#ifndef RCONFIGURATIONS
#define RCONFIGURATIONS

#include <string>

namespace rconfigurations {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const std::string PLAYER_IMAGE_FILE = "playerSprite.png";
	const std::string COIN_IMAGE_FILE = "coinSprite.png";
	

	enum spriteIndicies {
		PLAYER_SPRITE = 0,
		COIN_SPRITE = 1,
	};
}


#endif

