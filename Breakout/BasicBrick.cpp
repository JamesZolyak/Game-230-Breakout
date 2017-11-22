#include "BasicBrick.h"

BasicBrick::BasicBrick()
{

}

BasicBrick::BasicBrick(Vector2f dimensions, Texture* texture)
{
	health = 1;
	color = Color::Blue;
	brick.setSize(dimensions - sf::Vector2f(3, 3));
	brick.setTexture(texture);
	brick.setFillColor(color);
	brick.setOrigin(dimensions / 2.f);
	containsPowerUp = false;
}


BasicBrick::~BasicBrick()
{
}
