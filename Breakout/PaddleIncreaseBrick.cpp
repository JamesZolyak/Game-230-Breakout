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
	containsPowerUp = true;
	powerUp = new PaddleIncreasePowerUp(10.f, Color::Red);
	powerUp->speed = 200;
	powerUp->powerUp.setRadius(10 - 3);
	powerUp->powerUp.setOutlineThickness(3);
	powerUp->powerUp.setOutlineColor(color);
	powerUp->powerUp.setFillColor(color);
	powerUp->powerUp.setOrigin(10 / 2, 10 / 2);
	powerUp->powerUp.setPosition(brick.getPosition());
}

void PaddleIncreaseBrick::onHit(Paddle* player)
{
	health--;
}

PaddleIncreaseBrick::~PaddleIncreaseBrick()
{
}
