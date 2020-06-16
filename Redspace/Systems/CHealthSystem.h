#ifndef CHEALTHSYSTEM_H
#define CHEALTHSYSTEM_H

class CShotFiredEvent;
class CCollisionEvent;

class CHealthSystem : public ex::System<CHealthSystem>, public ex::Receiver<CHealthSystem>
{
private:
	struct DestroyInfo
	{
		ex::Entity object;
		ex::Entity bullet;
		sf::Vector2f placeOfDestroy;
		bool destroyedByPlayer = false;

		friend bool operator==(const DestroyInfo& left, const DestroyInfo& right)
		{
			return left.object == right.object && left.bullet == right.bullet && left.placeOfDestroy == right.placeOfDestroy && left.destroyedByPlayer == right.destroyedByPlayer;
		}

		friend bool operator==(const DestroyInfo& left, const ex::Entity& right)
		{
			return left.object == right;
		}
	};

	CGame& game;

	/* —сылка на окно */
	sf::RenderWindow& target;

	std::vector<DestroyInfo> destroyInfoList;

	std::vector<ex::Entity> playerBulletList;

public:
	/* Ѕазовый конструктор */
	explicit CHealthSystem(CGame& game, sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CShotFiredEvent& shotFiredEvent);

	void receive(const CCollisionEvent& collisionEvent);
};

#endif