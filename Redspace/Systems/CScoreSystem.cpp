#include <thread>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Core/CGame.h"
#include "../Enums/ObjectTypes.h"
#include "../Events/CPlayerDestroyedObjectEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CScoreComponent.h"

#include "CScoreSystem.h"

CScoreSystem::CScoreSystem(CGame& game, sf::RenderWindow& target)
	: game(game), target(target)
{ }

void CScoreSystem::configure(ex::EventManager& events)
{
	events.subscribe<CPlayerDestroyedObjectEvent>(*this);
}

void CScoreSystem::updateTextScoreVisibility(ScoreText& scoreText)
{
	float timeInSeconds = scoreText.lifeTime.getElapsedTime().asSeconds();
	
	int offset = scoreText.color.a + 15;
	int alpha = (offset < 255) ? offset : 255;

	if (timeInSeconds >= 0.5f)
	{
		offset = scoreText.color.a - 15;
		alpha = (offset > 0) ? offset : 0;
	}

	scoreText.color.a = alpha;

	scoreText.position.y -= 1.5f;
}

void CScoreSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity::Id playerId = this->game.getPlayerId();
	this->player = entities.get(playerId);

	for (int index = 0; index < this->scoreTexts.size(); index++)
	{
		std::thread(&CScoreSystem::updateTextScoreVisibility, this, std::ref(this->scoreTexts[index])).join();

		unsigned int score = this->scoreTexts[index].score;
		this->game.getSFMLRenderer()->createGameText("kenVector", 16, "+" + std::to_string(score), this->scoreTexts[index].position, this->scoreTexts[index].color);

		float timeInSeconds = this->scoreTexts[index].lifeTime.getElapsedTime().asSeconds();

		if (timeInSeconds >= 1.0f)
		{
			this->scoreTexts.erase(this->scoreTexts.begin() + index);
			index--;
		}
	}
}

void CScoreSystem::receive(const CPlayerDestroyedObjectEvent& playerDestroyedObjectEvent)
{
	ScoreText scoreText;
	scoreText.lifeTime.restart();

	scoreText.color = sf::Color::White;
	scoreText.color.a = 0;

	scoreText.score = 50;

	scoreText.position = playerDestroyedObjectEvent.getPlaceOfDestroy();

	this->scoreTexts.push_back(scoreText);

	ex::ComponentHandle<CScoreComponent> playerScoreComponent = this->player.component<CScoreComponent>();
	playerScoreComponent->addScore(scoreText.score);
}