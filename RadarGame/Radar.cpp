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
	if (radarBlinkState != OFF) {
		if ((transparencyLevel == 255 - RADAR_TRANSPARENCY_DELTA)&&radarBlinkState == UP) {
			transparencyLevel = 255;
			radarBlinkState = OFF;
		}
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
