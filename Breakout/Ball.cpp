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

void Ball::resetBall(Paddle* player)
{
	player->launchedBall = false;
	player->lives--;
	ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 30);
}

bool Ball::handlePlayerLife(Sound* s, int gameHeight, Paddle* player)
{
	if (ball.getPosition().y + radius > gameHeight)
	{
		s->play();
		resetBall(player);
		return true;
	}
	return false;
}

void Ball::handleWallCollision(Sound* s, int gameWidth, int gameHeight)
{
	if (ball.getPosition().x - radius < 0.f)
	{
		s->play();

		Vector2f c;
		c.x = cosf(ballAngle);
		c.y = sinf(ballAngle);

		ballAngle = atan2f(c.y, -c.x);
		ball.setPosition(radius + 10.1f, ball.getPosition().y);
		
	}
	if (ball.getPosition().x + radius > gameWidth)
	{
		s->play();
		float angleHigh = 1.5f * 3.14159265358f;
		float angleLow = 0.5f * 3.14159265358f;
		Vector2f c;
		c.x = cosf(ballAngle); 
		c.y = sinf(ballAngle); 

		ballAngle = atan2f(c.y, -c.x);

		//ballAngle = -ballAngle * (0.5f * 3.1415926f);
		ball.setPosition(gameWidth - radius - 10.1f, ball.getPosition().y);
	}
	if (ball.getPosition().y - radius < 0.f)
	{
		s->play();
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

		s->play();
		//ball.setPosition(player.paddle.getPosition().x + radius + player.dimensions.x / 2 + 20.0f, ball.getPosition().y);
		ball.setPosition(ball.getPosition().x, player.paddle.getPosition().y - radius - 25);
	}
}

bool Ball::handleBrickCollision(Sound* s, vector<vector<Brick*>> rows, Paddle* player)
{
	for (vector<Brick*> r : rows)
	{
		for (Brick* brick : r)
		{
			if (ball.getGlobalBounds().intersects(brick->brick.getGlobalBounds()) && brick->health > 0)
			{
				Vector2f temp = ball.getPosition() - brick->brick.getPosition();
				float angle = atan2f(temp.y, temp.x);
				ballAngle = angle;
				if (ball.getPosition().y > brick->brick.getPosition().y)
				{
					ball.setPosition(ball.getPosition().x, brick->brick.getPosition().y + radius + 20);
				}
				else if (ball.getPosition().y < brick->brick.getPosition().y)
				{
					ball.setPosition(ball.getPosition().x, brick->brick.getPosition().y - radius - 20);
				}
				
				
				s->play();
				brick->onHit(player);
				if (brick->color == Color::Green)
				{
					speed += 30;
				}
				if (brick->health <= 0)
				{
					player->bricksHit++;
				}
				return true;
			}
		}
	}
	return false;
}

Ball::~Ball()
{
}
