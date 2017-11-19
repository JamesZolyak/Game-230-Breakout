#include "DoubleHealthBrick.h"



DoubleHealthBrick::DoubleHealthBrick()
{
}

DoubleHealthBrick::DoubleHealthBrick(Vector2f dimensions, Texture* texture)
{
	health = 2;
	color = Color::Red;
	brick.setSize(dimensions - sf::Vector2f(3, 3));
	brick.setTexture(texture);
	brick.setFillColor(color);
	brick.setOrigin(dimensions / 2.f);
}

DoubleHealthBrick::~DoubleHealthBrick()
{
}
