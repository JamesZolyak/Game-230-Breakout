#pragma once
#include "PowerUp.h"
class PaddleIncreaseSpeedPowerUp :
	public PowerUp
{
public:
	PaddleIncreaseSpeedPowerUp(float f, Color color);
	void Activate(Paddle* player);
	~PaddleIncreaseSpeedPowerUp();
};

