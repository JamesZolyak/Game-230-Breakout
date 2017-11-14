#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "BasicBrick.h"
#include "DoubleHealthBrick.h"
#include <string>
#include <cmath>
#include <vector>

using namespace sf;
using namespace std;

const float pi = 3.14159f;
const int gameWidth = 800;
const int gameHeight = 600;

Paddle* player = new Paddle(Vector2f(100, 25));
Ball* ball = new Ball(10.0f);
vector<Brick*> firstRow;
vector<Brick*> secondRow;
vector<vector<Brick*>> rows;
bool isPlaying = false;
const int startingLives = 3;
int playerScore = 0;
const float startingX = 50;
const float startingY = 12.5f;
float initialX = 50;
float initialY = 12.5f;
Text playerScoreText;
Text playerLivesText;
Text lossText;

void brickSetup()
{
	for (int i = 0; i < 8; ++i)
	{
		DoubleHealthBrick* temp = new DoubleHealthBrick(Vector2f(100, 25));
		temp->brick.setPosition(initialX, initialY);
		firstRow.push_back(temp);
		initialX += 100;
	}
	initialY += 25;
	initialX = startingX;

	for (int i = 0; i < 8; ++i)
	{
		BasicBrick* temp = new BasicBrick(Vector2f(100, 25));
		temp->brick.setPosition(initialX, initialY);
		secondRow.push_back(temp);
		initialX += 100;
	}
	rows.push_back(secondRow);
	rows.push_back(firstRow);
}

void resetBoard()
{
	for (int i = 0; i < rows.size(); ++i)
	{
		rows[i].clear();
	}
	rows.clear();
	initialX = startingX;
	initialY = startingY;
	player->lives = startingLives;
	playerScore = 0;
	player->bricksHit = 0;
	playerLivesText.setString(to_string(player->lives));
	playerScoreText.setString(to_string(playerScore));
	player->paddle.setPosition(gameWidth / 2, gameHeight - 10);
	ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 25);
	player->launchedBall = false;
	brickSetup();
}

void nextLevel()
{
	for (int i = 0; i < rows.size(); ++i)
	{
		rows[i].clear();
	}
	rows.clear();
	initialX = startingX;
	initialY = startingY;
	player->bricksHit = 0;
	ball->speed += 50;
	playerLivesText.setString(to_string(player->lives));
	playerScoreText.setString(to_string(playerScore));
	player->paddle.setPosition(gameWidth / 2, gameHeight - 10);
	ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 25);
	player->launchedBall = false;
	brickSetup();
}

void resetCheck()
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		resetBoard();
	}
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	RenderWindow window(VideoMode(gameWidth, gameHeight), "Pong");
	Clock clock;
	Clock AITimer;
	const Time AITime = seconds(0.1f);
	player->speed = 250;
	ball->speed = 200;

	Font font;
	if (!font.loadFromFile("calibri.ttf"))
		return EXIT_FAILURE;

	playerScoreText.setFont(font);
	playerScoreText.setCharacterSize(40);
	playerScoreText.setPosition(80.f, 80.f);
	playerScoreText.setFillColor(Color::White);
	playerScoreText.setString(to_string(playerScore));

	playerLivesText.setFont(font);
	playerLivesText.setCharacterSize(40);
	playerLivesText.setPosition(700.f, 80.f);
	playerLivesText.setFillColor(Color::White);
	playerLivesText.setString(to_string(player->lives));

	lossText.setFont(font);
	lossText.setCharacterSize(40);
	lossText.setPosition(gameWidth/2, gameHeight/2);
	lossText.setFillColor(Color::White);
	lossText.setString("You Lose!\nPress P to play again!");

	Sound paddleBounceSound;
	SoundBuffer paddleBounceBuffer;
	paddleBounceBuffer.loadFromFile("Bounce.wav");
	paddleBounceSound.setBuffer(paddleBounceBuffer);

	Sound wallBounceSound;
	SoundBuffer wallBounceBuffer;
	wallBounceBuffer.loadFromFile("WallBounce.wav");
	wallBounceSound.setBuffer(wallBounceBuffer);

	Sound ballLossSound;
	SoundBuffer ballLossBuffer;
	ballLossBuffer.loadFromFile("BallLoss.wav");
	ballLossSound.setBuffer(ballLossBuffer);

	Sound brickDamageSound;
	SoundBuffer brickDamageBuffer;
	brickDamageBuffer.loadFromFile("BrickDamage.wav");
	brickDamageSound.setBuffer(brickDamageBuffer);

	Sound brickDestroySound;
	SoundBuffer brickDestroyBuffer;
	brickDestroyBuffer.loadFromFile("BrickDestroy.wav");
	brickDestroySound.setBuffer(brickDestroyBuffer);

	player->paddle.setPosition(gameWidth / 2, gameHeight - 10);
	ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 25);

	brickSetup();
	do
	{
		ball->ballAngle = (std::rand() % 360) * 2 * pi / 360;
	} while (std::abs(std::cos(ball->ballAngle)) > 0.5f);

	while (window.isOpen())
	{
		if (!isPlaying)
		{
			clock.restart();
			isPlaying = true;
		}
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (player->lives > 0)
		{
			float deltaTime = clock.restart().asSeconds();
			player->handlePlayerMovement(deltaTime, gameWidth);
			player->launchBall();
			if (player->launchedBall)
				ball->handleBallMovement(deltaTime);
			else
				ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 30);

			ball->handleWallCollision(&wallBounceSound, gameWidth, gameHeight);
			ball->handlePaddleCollision(&paddleBounceSound, *player);
			if (ball->handleBrickCollision(&brickDestroySound, rows, player))
			{
				playerScore += 100;
				playerScoreText.setString(to_string(playerScore));
			}

			if (ball->handlePlayerLife(&ballLossSound, gameHeight, player))
				playerLivesText.setString(to_string(player->lives));
		}

		if (0 == (rows[0].size() + rows[1].size()))
		{
			nextLevel();
		}


		window.clear();
		window.draw(playerScoreText);
		window.draw(playerLivesText);
		if (player->lives > 0)
		{
			window.draw(player->paddle);
			window.draw(ball->ball);

			for (int j = 0; j < rows.size(); ++j)
			{
				for (int k = 0; k < rows[j].size(); ++k)
				{
					if (rows[j][k]->health > 0)
						window.draw(rows[j][k]->brick);
					else
					{
						rows[j][k] = nullptr;
						rows[j].erase(rows[j].begin() + k);
					}
				}
			}
		}
		else
		{
			window.draw(lossText);
			ball->speed = 200;
			resetCheck();
		}
		
		window.display();
	}

	return 0;
}
