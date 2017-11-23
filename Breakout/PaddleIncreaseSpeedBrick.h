#pragma once
#include "Brick.h"
#include "PaddleIncreaseSpeedPowerUp.h"

class PaddleIncreaseSpeedBrick :
	public Brick
{
public:
	void onHit(Paddle* player);
	PaddleIncreaseSpeedBrick();
	PaddleIncreaseSpeedBrick(Vector2f dimensions, Texture* texture);
	~PaddleIncreaseSpeedBrick();
};

