#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include <unordered_map>
#include "ActorRace.hpp"
#include "FileParser.hpp"

class ActorFactory {
	private:
	std::unordered_map<const char*, ActorRace*> m_mTaxonomy = {};

	public:
	ActorFactory();
	~ActorFactory();
	E_FileParsingResult parseTaxonomy(const char* taxonomyFile);
	void addActorRaceTaxonomy(const char* name, ActorRace* race);
};

#endif
