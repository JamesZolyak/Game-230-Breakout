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
#include "BallSpeedBrick.h"
#include "PaddleIncreaseBrick.h"
#include "PaddleIncreaseSpeedBrick.h"
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
vector<Brick*> thirdRow;
vector<Brick*> fourthRow;
vector<vector<Brick*>> rows;
bool isPlaying = false;
const int startingLives = 3;
const int startingSpeed = 300;
int playerScore = 0;
const float startingX = 80;
const float startingY = 60;
float initialX = 80;
float initialY = 60;
Text playerScoreText;
Text playerLivesText;
Text lossText;
Texture texture;
Texture image;
Sprite background;
const int brickWidth = 75;
const int brickHeight = 25;


void brickSetup()
{
	firstRow.clear();
	secondRow.clear();
	thirdRow.clear();
	fourthRow.clear();
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	for (int i = 0; i < 8; ++i)
	{
		Brick* temp;
		int tempNum = rand() % 100;
		if (tempNum >= 0 && tempNum <= 54)
			temp = new BasicBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 55 && tempNum <= 76)
			temp = new DoubleHealthBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 77 && tempNum <= 87)
			temp = new PaddleIncreaseBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 88 && tempNum <= 93)
			temp = new PaddleIncreaseSpeedBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 94 && tempNum <= 99)
			temp = new BallSpeedBrick(Vector2f(brickWidth, brickHeight), &texture);

		temp->brick.setPosition(initialX, initialY);
		firstRow.push_back(temp);
		initialX += 90;
	}
	initialY += 35;
	initialX = startingX;

	for (int i = 0; i < 8; ++i)
	{
		Brick* temp;
		int tempNum = rand() % 100;
		if (tempNum >= 0 && tempNum <= 54)
			temp = new BasicBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 55 && tempNum <= 76)
			temp = new DoubleHealthBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 77 && tempNum <= 87)
			temp = new PaddleIncreaseBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 88 && tempNum <= 93)
			temp = new PaddleIncreaseSpeedBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 94 && tempNum <= 99)
			temp = new BallSpeedBrick(Vector2f(brickWidth, brickHeight), &texture);

		temp->brick.setPosition(initialX, initialY);
		secondRow.push_back(temp);
		initialX += 90;
	}

	initialY += 35;
	initialX = startingX;

	for (int i = 0; i < 8; ++i)
	{
		Brick* temp;
		int tempNum = rand() % 100;
		if (tempNum >= 0 && tempNum <= 54)
			temp = new BasicBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 55 && tempNum <= 76)
			temp = new DoubleHealthBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 77 && tempNum <= 87)
			temp = new PaddleIncreaseBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 88 && tempNum <= 93)
			temp = new PaddleIncreaseSpeedBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 94 && tempNum <= 99)
			temp = new BallSpeedBrick(Vector2f(brickWidth, brickHeight), &texture);

		temp->brick.setPosition(initialX, initialY);
		thirdRow.push_back(temp);
		initialX += 90;
	}

	initialY += 35;
	initialX = startingX;

	for (int i = 0; i < 8; ++i)
	{
		Brick* temp;
		int tempNum = rand() % 100;
		if (tempNum >= 0 && tempNum <= 54)
			temp = new BasicBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 55 && tempNum <= 76)
			temp = new DoubleHealthBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 77 && tempNum <= 87)
			temp = new PaddleIncreaseBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 88 && tempNum <= 93)
			temp = new PaddleIncreaseSpeedBrick(Vector2f(brickWidth, brickHeight), &texture);
		else if (tempNum >= 94 && tempNum <= 99)
			temp = new BallSpeedBrick(Vector2f(brickWidth, brickHeight), &texture);

		temp->brick.setPosition(initialX, initialY);
		fourthRow.push_back(temp);
		initialX += 90;
	}
	rows.push_back(fourthRow);
	rows.push_back(thirdRow);
	rows.push_back(secondRow);
	rows.push_back(firstRow);
}

void resetBoard()
{
	for (int i = 0; i < rows.size(); ++i)
	{
		for (int j = 0; j < rows[i].size(); ++j)
		{
			delete rows[i][j];
			rows[i][j] = nullptr;
		}
		rows[i].clear();
	}
	rows.clear();
	//rows.swap(vector<vector<Brick*>>());
	initialX = startingX;
	initialY = startingY;
	player->lives = startingLives;
	playerScore = 0;
	player->bricksHit = 0;
	playerLivesText.setString(to_string(player->lives));
	playerScoreText.setString(to_string(playerScore));
	player->paddle.setPosition(gameWidth / 2, gameHeight - 10);
	player->paddle.setSize(Vector2f(100, 25) - sf::Vector2f(3, 3));
	player->speed = 250;
	ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 25);
	player->launchedBall = false;
	brickSetup();
}

void nextLevel()
{
	for (int i = 0; i < rows.size(); ++i)
	{
		for (int j = 0; j < rows[i].size(); ++j)
		{
			delete rows[i][j];
			rows[i][j] = nullptr;
		}
		rows[i].clear();
	}
	rows.clear();
	initialX = startingX;
	initialY = startingY;
	player->bricksHit = 0;
	ball->speed += 100;
	playerLivesText.setString(to_string(player->lives));
	playerScoreText.setString(to_string(playerScore));
	player->paddle.setPosition(gameWidth / 2, gameHeight - 10);
	ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 25);
	player->launchedBall = false;
	brickSetup();
}

void resetCheck()
{
	player->paddle.setPosition(gameWidth / 2, gameHeight - 10);
	ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 25);
	player->launchedBall = false;
	if (Keyboard::isKeyPressed(Keyboard::R))
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
	ball->speed = startingSpeed;

	Font font;
	if (!font.loadFromFile("calibri.ttf"))
		return EXIT_FAILURE;

	if (!texture.loadFromFile("2-brick-texture-free.jpg"))
		return EXIT_FAILURE;

	if (!image.loadFromFile("230-BreakoutBackground.png"))
		return EXIT_FAILURE;

	background.setTexture(image);

	playerScoreText.setFont(font);
	playerScoreText.setCharacterSize(40);
	playerScoreText.setPosition(60.f, 520.f);
	playerScoreText.setFillColor(Color::White);
	playerScoreText.setString("Score: " + to_string(playerScore));

	playerLivesText.setFont(font);
	playerLivesText.setCharacterSize(40);
	playerLivesText.setPosition(660.f, 520.f);
	playerLivesText.setFillColor(Color::White);
	playerLivesText.setString("Lives: " + to_string(player->lives));

	lossText.setFont(font);
	lossText.setCharacterSize(40);
	lossText.setPosition(gameWidth/2 - 100, gameHeight/2 - 100);
	lossText.setFillColor(Color::White);
	lossText.setString("You Lose!\nPress R to play again!");

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

	Sound newLevelSound;
	SoundBuffer newLevelBuffer;
	newLevelBuffer.loadFromFile("NewLevel.wav");
	newLevelSound.setBuffer(newLevelBuffer);

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

			if (ball->powerUps.size() > 0)
			{
				for (PowerUp* powerUp : ball->powerUps)
				{
					powerUp->HandleMovement(deltaTime);
				}
			}

			ball->handleWallCollision(&wallBounceSound, gameWidth, gameHeight);
			ball->handlePaddleCollision(&paddleBounceSound, *player);
			
			ball->handlePowerUpCollision(&paddleBounceSound, player);

			if (ball->handleBrickCollision(&brickDestroySound, rows, player))
			{
				playerScore += 100;
				playerScoreText.setString("Score: " + to_string(playerScore));
			}

			if (ball->handlePlayerLife(&ballLossSound, gameHeight, player))
				playerLivesText.setString("Lives: " + to_string(player->lives));
		}

		if (0 == (rows[0].size() + rows[1].size() + rows[2].size() + rows[3].size()))
		{
			newLevelSound.play();
			nextLevel();
		}


		window.clear();
		window.draw(background);
		window.draw(playerScoreText);
		window.draw(playerLivesText);
		if (player->lives > 0)
		{
			window.draw(player->paddle);
			window.draw(ball->ball);
			if (ball->powerUps.size() > 0)
			{
				for (PowerUp* powerUp : ball->powerUps)
				{
					window.draw(powerUp->powerUp);
				}
			}

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
			ball->speed = startingSpeed;
			resetCheck();
		}
		
		window.display();
	}

	return 0;
}
