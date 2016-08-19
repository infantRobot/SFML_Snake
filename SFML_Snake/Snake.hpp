#pragma once

#include <SFML\Graphics.hpp>
#include <list>

class Snake
{
public:
	Snake();

	void draw(sf::RenderWindow &window);

	void update(sf::Time dt);

	void createFood();

	void restart();

private:
	bool isAlive = true;
	int snakeSize;
	sf::Vector2i foodPos;
	std::list<sf::Vector2i> snakePos;
	int xSpeed;
	int ySpeed;
	float deltaT;
	const float FRAMERATE = 0.1f;
	const int SIZE = 20;
	const int SCALE = 30;
	const int BOARDER = 10;
};

