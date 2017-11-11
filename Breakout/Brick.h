#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Brick
{
public:
	RectangleShape brick;
	Vector2f position;
	Vector2f dimensions;
	int health;
	Color color;

	void onHit();
	Brick();
	Brick(Vector2f dimensions);
	~Brick();
};

