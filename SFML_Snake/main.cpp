#include <SFML/Graphics.hpp>


#include "Snake.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	Snake player;

	window.setFramerateLimit(60);

	sf::Clock clock;
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
		}
		
		window.clear();

		player.update(clock.restart());
		player.draw(window);

		window.display();
	}

	return 0;
}