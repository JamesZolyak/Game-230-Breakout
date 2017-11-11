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
#include <string>
#include <cmath>

using namespace sf;
using namespace std;

const float pi = 3.14159f;
const int gameWidth = 800;
const int gameHeight = 600;

Paddle* player = new Paddle(Vector2f(100, 25));
Ball* ball = new Ball(10.0f);
BasicBrick* b = new BasicBrick(Vector2f(100, 25));
bool isPlaying = false;
int playerScore = 0;
int playerLives = 0;

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

	Text playerScoreText;
	playerScoreText.setFont(font);
	playerScoreText.setCharacterSize(40);
	playerScoreText.setPosition(80.f, 80.f);
	playerScoreText.setFillColor(Color::White);
	playerScoreText.setString(to_string(playerScore));

	Text playerLivesText;
	playerLivesText.setFont(font);
	playerLivesText.setCharacterSize(40);
	playerLivesText.setPosition(700.f, 80.f);
	playerLivesText.setFillColor(Color::White);
	playerLivesText.setString(to_string(playerLives));

	SoundBuffer sb;
	sb.loadFromFile("Bounce.wav");
	Sound s;
	s.setBuffer(sb);

	player->paddle.setPosition(gameWidth / 2, gameHeight - 10);
	ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 25);
	b->brick.setPosition(gameWidth / 2, gameHeight / 2 - 100);
	do
	{
		ball->ballAngle = (std::rand() % 360) * 2 * pi / 360;
		playerScore = ball->ballAngle;
		playerScoreText.setString(to_string(playerScore));
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

		
		float deltaTime = clock.restart().asSeconds();
		player->handlePlayerMovement(deltaTime, gameWidth);
		player->launchBall();
		if (player->launchedBall)
			ball->handleBallMovement(deltaTime);
		else
			ball->ball.setPosition(player->paddle.getPosition().x, player->paddle.getPosition().y - 30);

		ball->handleWallCollision(&s, gameWidth, gameHeight);
		ball->handlePaddleCollision(&s, *player);
		ball->handleBrickCollision(&s, b);

		window.clear();
		window.draw(playerScoreText);
		window.draw(playerLivesText);
		window.draw(player->paddle);
		window.draw(ball->ball);
		if (b->health > 0)
		{
			window.draw(b->brick);
		}
		
		window.display();
	}

	return 0;
}
