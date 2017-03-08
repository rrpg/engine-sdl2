#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include <vector>
#include "ActorRace.hpp"
#include "Actor.hpp"
#include "FileParser.hpp"

enum E_ActorRaces {RACE_HUMAN, RACE_DEMON, NB_RACES};

class ActorFactory {
	private:
	std::vector<ActorRace*> m_mTaxonomy = {};

	public:
	ActorFactory();
	~ActorFactory();
	E_FileParsingResult parseTaxonomy(const char* taxonomyFile);
	void addActorRaceTaxonomy(ActorRace* race);
	Actor* createActor(E_ActorRaces race);
};

#endif
