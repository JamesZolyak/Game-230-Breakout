#include "Ball.h"

using namespace sf;
using namespace std;
Ball::Ball(float f)
{
	radius = f;
	ball.setRadius(radius - 3);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(Color::White);
	ball.setFillColor(Color::White);
	ball.setOrigin(radius / 2, radius / 2);
}

void Ball::handleBallMovement(float deltaTime)
{
	float factor = speed * deltaTime;
	ball.move(cos(ballAngle) * factor, sin(ballAngle) * factor);
}

bool Ball::handleEnemyScoreCollision()
{
	if (ball.getPosition().x - radius < 0.f)
	{
		ball.setPosition(400, 200);
		speed = 200;
		return true;
	}
	return false;
}

bool Ball::handlePlayerScoreCollision(int gameWidth)
{
	if (ball.getPosition().x + radius > gameWidth)
	{
		ball.setPosition(400, 200);
		speed = 200;
		return true;
	}
	return false;
}

void Ball::handleWallCollision(Sound* s, int gameWidth, int gameHeight)
{
	if (ball.getPosition().x - radius < 0.f)
	{
		//s->play();
		ballAngle = -ballAngle * 90;
		ball.setPosition(radius + 10.1f, ball.getPosition().y);
		
	}
	if (ball.getPosition().x + radius > gameWidth)
	{
		//s->play();
		ballAngle = -ballAngle * 90;
		ball.setPosition(gameWidth - radius - 10.1f, ball.getPosition().y);
	}
	if (ball.getPosition().y - radius < 0.f)
	{
		//s->play();
		ballAngle = -ballAngle;
		ball.setPosition(ball.getPosition().x, radius + 0.1f);
	}
}

void Ball::handlePaddleCollision(Sound* s, Paddle player)
{
	if (ball.getGlobalBounds().intersects(player.paddle.getGlobalBounds()))
	{
		Vector2f temp = ball.getPosition() - player.paddle.getPosition();
		float angle = atan2f(temp.y, temp.x);
		ballAngle = angle;

		//s->play();
		//ball.setPosition(player.paddle.getPosition().x + radius + player.dimensions.x / 2 + 20.0f, ball.getPosition().y);
		ball.setPosition(ball.getPosition().x, player.paddle.getPosition().y - radius - 25);
	}
}

void Ball::handleBrickCollision(Sound* s, Brick* brick)
{
	if (ball.getGlobalBounds().intersects(brick->brick.getGlobalBounds()))
	{
		Vector2f temp = ball.getPosition() - brick->brick.getPosition();
		float angle = atan2f(temp.y, temp.x);
		ballAngle = angle;
		ball.setPosition(ball.getPosition().x, brick->brick.getPosition().y + radius + 25);

		brick->onHit();
	}
}

Ball::~Ball()
{
}
