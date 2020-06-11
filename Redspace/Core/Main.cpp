#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "CGame.h"
#include "../Enums/GameStates.h"

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

	game.setGameState(GameStates::Unpaused);

	sf::Clock clock;
	ex::TimeDelta timeDelta;

	while (window.isOpen())
	{
		sf::Event event = sf::Event();

		game.pollEvent(event);

		if (window.hasFocus())
		{
			window.clear(sf::Color::White);

			timeDelta = clock.restart().asSeconds();
			game.update(timeDelta);

			window.display();
		}
	}
}