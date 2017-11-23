#include "PaddleIncreaseSpeedPowerUp.h"



PaddleIncreaseSpeedPowerUp::PaddleIncreaseSpeedPowerUp(float f, Color color)
{
	radius = f;
	powerUp.setRadius(radius - 3);
	powerUp.setOutlineThickness(3);
	powerUp.setOutlineColor(color);
	powerUp.setFillColor(color);
	powerUp.setOrigin(radius / 2, radius / 2);
}

void PaddleIncreaseSpeedPowerUp::Activate(Paddle* player)
{
	player->speed += 20;
}

PaddleIncreaseSpeedPowerUp::~PaddleIncreaseSpeedPowerUp()
{
}
