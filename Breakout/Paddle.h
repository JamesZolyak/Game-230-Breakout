#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;
using namespace std;

class Paddle
{
public:
	RectangleShape paddle;
	Vector2f position;
	Vector2f paddleDimensions;
	int speed;
	bool launchedBall = false;
	int lives;
	int bricksHit;
	Paddle(Vector2f dimensions);
	void handlePlayerMovement(float deltaTime, int gameWidth);
	void launchBall();
	~Paddle();
};

