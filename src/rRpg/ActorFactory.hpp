#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include <vector>
#include <memory>
#include "Behaviour/Factory.hpp"
#include "GUI/Factory.hpp"
#include "ActorRace.hpp"
#include "Actor.hpp"
#include "dataTypes.hpp"

class ActorFactory {
	private:
	std::vector<ActorRace> m_mTaxonomy = {};
	BehaviourFactory m_behaviourFactory;
	GraphicFactory m_graphicFactory;

	public:
	ActorFactory();
	~ActorFactory();
	bool parseTaxonomy(const char* taxonomyFile);
	std::shared_ptr<Actor> createActor(E_ActorRaces race);
	std::shared_ptr<Actor> createEnemy(E_ActorRaces race);
	std::shared_ptr<Actor> createHero();
};

#endif
