#include "Brick.h"

Brick::Brick()
{

}

Brick::Brick(Vector2f dimensions)
{
	brick.setSize(dimensions - sf::Vector2f(3, 3));
	brick.setOutlineThickness(3);
	brick.setOutlineColor(sf::Color::Black);
	brick.setFillColor(color);
	brick.setOrigin(dimensions / 2.f);
}

void Brick::onHit()
{
	health--;
}


Brick::~Brick()
{
}