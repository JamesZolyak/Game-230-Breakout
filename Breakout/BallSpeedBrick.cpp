#include "BallSpeedBrick.h"

BallSpeedBrick::BallSpeedBrick()
{

}

BallSpeedBrick::BallSpeedBrick(Vector2f dimensions, Texture* texture)
{
	health = 1;
	color = Color::Green;
	brick.setSize(dimensions - sf::Vector2f(3, 3));
	brick.setTexture(texture);
	brick.setFillColor(color);
	brick.setOrigin(dimensions / 2.f);
}

BallSpeedBrick::~BallSpeedBrick()
{
}
