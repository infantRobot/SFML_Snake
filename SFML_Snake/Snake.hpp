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

private:
	bool isAlive = true;
	int snakeSize = 1;
	sf::Vector2i foodPos;
	std::list<sf::Vector2i> snakePos;
	int xSpeed;
	int ySpeed;
	float deltaT = 0;
	const float FRAMERATE = 0.1;
	const int SIZE = 20;
	const int SCALE = 30;
};

