#pragma once
#include "PowerUp.h"
class PaddleIncreasePowerUp :
	public PowerUp
{
public:
	PaddleIncreasePowerUp(float f, Color color);
	
	void Activate(Paddle* player);

	~PaddleIncreasePowerUp();
};

