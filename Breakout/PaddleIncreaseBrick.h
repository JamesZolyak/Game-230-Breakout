#pragma once
#include "Brick.h"
class PaddleIncreaseBrick :
	public Brick
{
public:
	void onHit(Paddle* player);
	PaddleIncreaseBrick();
	PaddleIncreaseBrick(Vector2f dimensions, Texture* texture);
	~PaddleIncreaseBrick();
};

