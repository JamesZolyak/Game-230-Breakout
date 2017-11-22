#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Paddle.h"
using namespace sf;

class PowerUp
{
public:
	CircleShape powerUp;
	Vector2f position;
	float radius;
	int speed;
	Color color;
	PowerUp();
	PowerUp(float f, Color color);
	void HandleMovement(float deltaTime);
	virtual void Activate(Paddle* player);
	~PowerUp();
};

