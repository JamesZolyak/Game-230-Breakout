#include "PaddleIncreaseBrick.h"



PaddleIncreaseBrick::PaddleIncreaseBrick()
{
}

PaddleIncreaseBrick::PaddleIncreaseBrick(Vector2f dimensions, Texture* texture)
{
	health = 1;
	color = Color::Magenta;
	brick.setSize(dimensions - sf::Vector2f(3, 3));
	brick.setTexture(texture);
	brick.setFillColor(color);
	brick.setOrigin(dimensions / 2.f);
}

void PaddleIncreaseBrick::onHit(Paddle* player)
{
	player->paddleDimensions.x += 20;
	player->paddle.setSize(player->paddleDimensions - sf::Vector2f(3, 3));
	player->paddle.setOrigin(player->paddleDimensions / 2.f);
	health--;
}

PaddleIncreaseBrick::~PaddleIncreaseBrick()
{
}
