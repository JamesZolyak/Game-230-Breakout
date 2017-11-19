#include "Paddle.h"



Paddle::Paddle(Vector2f dimensions)
{
	paddleDimensions = dimensions;
	paddle.setSize(paddleDimensions - sf::Vector2f(3, 3));
	paddle.setOutlineThickness(3);
	paddle.setOutlineColor(sf::Color::Black);
	paddle.setFillColor(sf::Color(100, 100, 200));
	paddle.setOrigin(paddleDimensions / 2.f);
	lives = 3;
	bricksHit = 0;
}

void Paddle::handlePlayerMovement(float deltaTime, int gameWidth)
{
	if (Keyboard::isKeyPressed(Keyboard::A) && (paddle.getPosition().x - paddleDimensions.x / 2 > 0))
	{
		paddle.move(-speed * deltaTime, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && (paddle.getPosition().x + paddleDimensions.x / 2 < gameWidth ))
	{
		paddle.move(speed * deltaTime, 0.f);
	}
}

void Paddle::launchBall()
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
		launchedBall = true;
}
Paddle::~Paddle()
{
}
