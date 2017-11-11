#include "BasicBrick.h"

BasicBrick::BasicBrick()
{

}

BasicBrick::BasicBrick(Vector2f dimensions)
{
	health = 1;
	color = Color::White;
	brick.setSize(dimensions - sf::Vector2f(3, 3));
	brick.setOutlineThickness(3);
	brick.setOutlineColor(sf::Color::Black);
	brick.setFillColor(color);
	brick.setOrigin(dimensions / 2.f);
}


BasicBrick::~BasicBrick()
{
}