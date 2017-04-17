#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include <vector>
#include "BehaviourFactory.hpp"
#include "GraphicFactory.hpp"
#include "ActorRace.hpp"
#include "Actor.hpp"
#include "Parser/File.hpp"

enum E_ActorRaces {RACE_HUMAN, RACE_DEMON, NB_RACES};

class ActorFactory {
	private:
	std::vector<ActorRace*> m_mTaxonomy = {};
	BehaviourFactory m_behaviourFactory;
	GraphicFactory m_graphicFactory;

	public:
	ActorFactory();
	~ActorFactory();
	E_FileParsingResult parseTaxonomy(const char* taxonomyFile);
	void addActorRaceTaxonomy(ActorRace* race);
	Actor* createActor(E_ActorRaces race);
	Actor* createRandomFoe();
	Actor* createHero();
};

#endif
