#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Brick.h"

using namespace sf;

class BasicBrick :
	public Brick
{
public:
	BasicBrick();
	BasicBrick(Vector2f dimensions, Texture* texture);
	~BasicBrick();
};

