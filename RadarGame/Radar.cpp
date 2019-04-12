#include "Radar.h"

Radar::Radar(RTexture* radTexture) : radarTexture(radTexture){
	radarTexture->setBlendMode();
}

void Radar::setAlpha(Uint8 alpha) {
	radarTexture->setAlpha(alpha);
}

bool Radar::renderToScreen(SDL_Renderer*& destinationRenderer) {
	return (radarTexture->renderCurrentTextureToFullScreen(0, 0, destinationRenderer));
}

void Radar::startBlink() {
	radarBlinkState = DOWN;
}
void Radar::updateBlink() {
	//"Bounce" the transparency level from 255, to MIN, and back to 255, by DELTA amount of change

	if (radarBlinkState != OFF) {
		//If blink is increasing and we're on the last increment before ending the blink, increment and end blink
		if ((transparencyLevel == 255 - RADAR_TRANSPARENCY_DELTA) && radarBlinkState == UP) {
			transparencyLevel = 255;
			radarBlinkState = OFF;
		}
		//If blink is decreasing and we've reached MIN, increment and change direction to increasing
		else if ((transparencyLevel == RADAR_TRANSPARENCY_MIN) && radarBlinkState == DOWN) {
			transparencyLevel = RADAR_TRANSPARENCY_MIN + RADAR_TRANSPARENCY_DELTA;
			radarBlinkState = UP;
		}
		else if (radarBlinkState == DOWN) {
			transparencyLevel -= RADAR_TRANSPARENCY_DELTA;
		}
		else if (radarBlinkState == UP) {
			transparencyLevel += RADAR_TRANSPARENCY_DELTA;
		}
		setAlpha(transparencyLevel);
	}
}

bool Radar::isBlinking() {
	return (radarBlinkState != OFF);
}
