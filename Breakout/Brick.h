#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Paddle.h"
#include "PowerUp.h"
using namespace sf;

class Brick
{
public:
	RectangleShape brick;
	Vector2f position;
	Vector2f dimensions;
	int health;
	Color color;
	Sprite sprite;
	bool containsPowerUp;
	PowerUp* powerUp;
	Brick();
	Brick(Vector2f dimensions, Texture* texture);
	virtual void onHit(Paddle* player);
	~Brick();
};

