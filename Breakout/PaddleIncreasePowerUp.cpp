#include "PaddleIncreasePowerUp.h"



PaddleIncreasePowerUp::PaddleIncreasePowerUp(float f, Color color)
{
	radius = f;
	powerUp.setRadius(radius - 3);
	powerUp.setOutlineThickness(3);
	powerUp.setOutlineColor(color);
	powerUp.setFillColor(color);
	powerUp.setOrigin(radius / 2, radius / 2);
}

void PaddleIncreasePowerUp::Activate(Paddle* player)
{
	player->paddleDimensions.x += 20;
	player->paddle.setSize(player->paddleDimensions - sf::Vector2f(3, 3));
	player->paddle.setOrigin(player->paddleDimensions / 2.f);
}

PaddleIncreasePowerUp::~PaddleIncreasePowerUp()
{
}
