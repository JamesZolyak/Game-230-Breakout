#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Paddle.h"
#include "Brick.h"
#include "PowerUp.h"
#include <string>
#include <cmath>
#include <vector>

using namespace sf;
using namespace std;

class Ball
{
public:
	CircleShape ball;
	Vector2f position;
	float radius;
	float ballAngle;
	int speed;
	vector<PowerUp*> powerUps;
	Ball(float f);

	void handleBallMovement(float deltaTime);
	void resetBall(Paddle* player);
	bool handlePlayerLife(Sound* s, int gameHeight, Paddle* player);
	void handleWallCollision(Sound* s, int gameWidth, int gameHeight);
	void handlePaddleCollision(Sound* s, Paddle player);
	bool handleBrickCollision(Sound* s, vector<vector<Brick*>> rows, Paddle* player);
	void handlePowerUpCollision(Sound* s, Paddle* player);
	~Ball();
};

