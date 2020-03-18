#include "Main.h"

int main()
{
	sf::VideoMode videoMode(800, 600);

	sf::RenderWindow window;
	window.create
	(
		videoMode,
		"Redspace"
	);

	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(false);

	CGame game(window);

	sf::Clock clock;
	ex::TimeDelta timeDelta;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (window.hasFocus())
		{
			window.clear(sf::Color::White);

			timeDelta = clock.restart().asSeconds();
			game.update(timeDelta);

			window.display();
		}
	}
}