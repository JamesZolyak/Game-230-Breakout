#include "PowerUp.h"

using namespace sf;
using namespace std;

PowerUp::PowerUp()
{

}

PowerUp::PowerUp(float f, Color color)
{
	speed = 250;
	radius = f;
	powerUp.setRadius(radius - 3);
	powerUp.setOutlineThickness(3);
	powerUp.setOutlineColor(color);
	powerUp.setFillColor(color);
	powerUp.setOrigin(radius / 2, radius / 2);
}

void PowerUp::HandleMovement(float deltaTime)
{
	powerUp.move(0.0f, speed * deltaTime);
}

void PowerUp::Activate(Paddle* player)
{

}

PowerUp::~PowerUp()
{
}
