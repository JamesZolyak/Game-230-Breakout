#include "Brick.h"

Brick::Brick()
{
}

Brick::Brick(Vector2f dimensions, Texture* texture)
{
	brick.setSize(dimensions - sf::Vector2f(3, 3));
	
	brick.setOrigin(dimensions / 2.f);
	brick.setTexture(texture);
	brick.setFillColor(color);
	containsPowerUp = false;
}

void Brick::onHit(Paddle* player)
{
	health--;
}


Brick::~Brick()
{
}
