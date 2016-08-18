#include "Snake.hpp"
#include <list>

#include <iostream>
#include <cstdlib>

Snake::Snake():xSpeed(1), ySpeed(0)
{
	//Initial position
	snakePos.push_back(sf::Vector2i(0, 0));

	srand(time(0));
	createFood();
}


void Snake::createFood()
{
	foodPos = sf::Vector2i(rand() % (600/SCALE), rand() % (600 / SCALE));

	//check that the food is not on the snake
	for (std::list<sf::Vector2i>::iterator it = snakePos.begin(); it != snakePos.end(); it++)
	{
		if (foodPos == (*it))
		{
			createFood();
		}
	}
}

void Snake::update(sf::Time dt)
{
	deltaT += dt.asSeconds();
	//std::cout << deltaT << std::endl;

	sf::Vector2i newPos = sf::Vector2i(xSpeed + snakePos.front().x, ySpeed + snakePos.front().y);
	if (newPos.x < 0 || newPos.x > SIZE-1 || newPos.y < 0 || newPos.y > SIZE-1)
	{
		isAlive = false;
	}
	if (deltaT > FRAMERATE && isAlive)
	{
		if (newPos == foodPos) 
		{
			snakeSize++;

			snakePos.push_front(newPos);
			createFood();
		}
		else
		{
			snakePos.push_front(newPos);
			snakePos.pop_back();
		}
		deltaT = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && xSpeed != 1)
	{
		xSpeed = -1;
		ySpeed = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && xSpeed != -1)
	{
		xSpeed = 1;
		ySpeed = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ySpeed != 1)
	{
		xSpeed = 0;
		ySpeed = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ySpeed != -1)
	{
		xSpeed = 0;
		ySpeed = 1;
	}

}

void Snake::draw(sf::RenderWindow &window)
{
	//draw all of the snake
	for (std::list<sf::Vector2i>::iterator it=snakePos.begin(); it != snakePos.end(); it++)
	{
		sf::RectangleShape limb(sf::Vector2f(SCALE,SCALE));
		limb.setFillColor(sf::Color::White);
		limb.setOutlineThickness(1.0f);
		limb.setOutlineColor(sf::Color::Green);
		limb.setPosition(sf::Vector2f((*it).x*SCALE, (*it).y*SCALE));

		window.draw(limb);
	}

	//draw the food
	sf::RectangleShape food(sf::Vector2f(SCALE, SCALE));
	food.setFillColor(sf::Color::Red);
	food.setPosition(sf::Vector2f(foodPos.x*SCALE, foodPos.y*SCALE));
	window.draw(food);
}
