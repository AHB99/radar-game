#ifndef COIN
#define COIN

#include "GameObject.h"
class RTexture;

class Coin : public GameObject {

public:
	Coin() = default;
	Coin(RTexture* gameObjectTexture, int xPos = 0, int yPos = 0);



};

#endif