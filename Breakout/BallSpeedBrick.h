#pragma once
#include "Brick.h"

class BallSpeedBrick :
	public Brick
{
public:

	BallSpeedBrick();
	BallSpeedBrick(Vector2f dimensions, Texture* texture);
	~BallSpeedBrick();
};

