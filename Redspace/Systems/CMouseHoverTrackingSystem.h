#ifndef CMOUSEHOVERTRACKINGSYSTEM_H
#define CMOUSEHOVERTRACKINGSYSTEM_H

class CMouseHoverTrackingSystem : public ex::System<CMouseHoverTrackingSystem>
{
private:
	sf::RenderWindow& target;

	std::vector<ex::Entity> listOfHoveredObjects;

public:
	explicit CMouseHoverTrackingSystem(sf::RenderWindow& target);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif