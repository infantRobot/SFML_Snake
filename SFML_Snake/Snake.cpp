#include "Snake.hpp"
#include <list>

#include <iostream>
#include <cstdlib>
#include <string>

Snake::Snake()
{
	srand(time(0));
	//sets the snake ready to go with the food
	restart();
}

void Snake::restart()
{
	//make the snake alive again
	isAlive = true;
	//set initial values
	deltaT = 0;
	snakeSize = 1;
	//Clear the snake position;
	snakePos.clear();
	//set the speeds to the inital speed
	xSpeed = 1;
	ySpeed = 0;

	//Put in first snake head
	snakePos.push_back(sf::Vector2i(0, 0));

	//create a new peice of food
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
	if (deltaT > FRAMERATE)
	{
		sf::Vector2i newPos = sf::Vector2i(xSpeed + snakePos.front().x, ySpeed + snakePos.front().y);
		if (newPos.x < 0 || newPos.x > SIZE - 1 || newPos.y < 0 || newPos.y > SIZE - 1)
		{
			isAlive = false;
		}
		if (isAlive)
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
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		restart();
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
		limb.setPosition(sf::Vector2f((*it).x*SCALE + BOARDER, (*it).y*SCALE + BOARDER));

		window.draw(limb);
	}

	//draw the food
	sf::RectangleShape food(sf::Vector2f(SCALE, SCALE));
	food.setFillColor(sf::Color::Red);
	food.setPosition(sf::Vector2f(foodPos.x*SCALE + BOARDER, foodPos.y*SCALE + BOARDER) );
	window.draw(food);

	//Draw the score and boundries
	sf::RectangleShape wall(sf::Vector2f(SCALE*SIZE + BOARDER, BOARDER));
	wall.setFillColor(sf::Color::Cyan);
	wall.setPosition(0, 0);
	window.draw(wall);
	wall.setPosition(0, SCALE*SIZE + BOARDER);
	window.draw(wall);

	wall.setSize(sf::Vector2f(BOARDER, SCALE*SIZE));
	wall.setPosition(0, BOARDER);
	window.draw(wall);
	wall.setSize(sf::Vector2f(BOARDER, SCALE*SIZE+ BOARDER *2));
	wall.setPosition(SCALE*SIZE + BOARDER, 0);
	window.draw(wall);

	sf::Font font;
	font.loadFromFile("Open 24 Display St.ttf");
	sf::Text tittle;
	tittle.setFont(font);
	tittle.setString("Snake Game");
	tittle.setCharacterSize(36);
	tittle.setFillColor(sf::Color::White);
	tittle.setPosition(sf::Vector2f(SCALE*SIZE + 2.5 * BOARDER, BOARDER));
	window.draw(tittle);

	sf::Text score;
	score.setFont(font);
	score.setString("Score");
	score.setCharacterSize(24);
	score.setFillColor(sf::Color::White);
	score.setPosition(sf::Vector2f(SCALE*SIZE + 2.5 * BOARDER, BOARDER+36));
	window.draw(score);

	
	score.setString(std::to_string(snakeSize));
	score.setPosition(sf::Vector2f(SCALE*SIZE + 2.5 * BOARDER, BOARDER + 24+36));
	window.draw(score);
}
