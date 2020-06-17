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

	CGame game(window);

	game.setGameState(GameStates::Unpaused);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event = sf::Event();

		game.pollEvent(event);

		sf::Time elapsedTime = clock.getElapsedTime();
		ex::TimeDelta timeDelta = clock.restart().asSeconds();

		if (window.hasFocus())
		{
			window.clear(sf::Color::White);

			game.update(timeDelta, elapsedTime);

			window.display();
		}
	}
}