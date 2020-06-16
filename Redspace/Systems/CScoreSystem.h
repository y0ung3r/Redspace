#ifndef CSCORESYSTEM_H
#define CSCORESYSTEM_H

class CPlayerDestroyedObjectEvent;

class CScoreSystem : public ex::System<CScoreSystem>, public ex::Receiver<CScoreSystem>
{
private:
	struct ScoreText
	{
		sf::Clock lifeTime;
		sf::Vector2f position;
		sf::Color color;
		unsigned int score;

		friend bool operator==(const ScoreText& left, const ScoreText& right)
		{
			return left.lifeTime.getElapsedTime() == right.lifeTime.getElapsedTime() && left.position == right.position && left.color == right.color;
		}
	};

	CGame& game;

	/* —сылка на окно */
	sf::RenderWindow& target;

	ex::Entity player;

	std::vector<ScoreText> scoreTexts;

	ex::Entity playerBullet;

	void updateTextScoreVisibility(ScoreText& scoreText);

public:
	/* Ѕазовый конструктор */
	explicit CScoreSystem(CGame& game, sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CPlayerDestroyedObjectEvent& playerDestroyedObjectEvent);
};

#endif