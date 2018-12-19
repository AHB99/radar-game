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
