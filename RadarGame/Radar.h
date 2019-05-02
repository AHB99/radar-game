#ifndef RADAR
#define RADAR

#include <SDL.h>
#include <SDL_image.h>
#include "RTexture.h"
#include "rconfigurations.h"

enum blinkState {
	OFF = 0,
	UP = 1,
	DOWN = 2
};

//Must be so that once starting from 255, will cycle properly.
const int RADAR_TRANSPARENCY_DELTA = 5;
const int RADAR_TRANSPARENCY_MIN = 0;


class Radar {
public:
	Radar() = default;
	Radar(RTexture* radTexture);
	void setAlpha(Uint8 alpha);
	bool renderToScreen(SDL_Renderer*& destinationRenderer);
	
	void startBlink();
	//Will cycle through a blink once triggered, and will turn off when complete
	void updateBlink();
	bool isBlinking();

private:
	RTexture* radarTexture = nullptr;
	//State of whether cycling down, up, or not cycling.
	int radarBlinkState = OFF;
	Uint8 transparencyLevel = 255;

};
#endif 
