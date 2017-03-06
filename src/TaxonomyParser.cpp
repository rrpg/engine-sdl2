#include "TaxonomyParser.hpp"
#include "ActorRace.hpp"
#include <iostream>

const int MAX_CHAR_RACE_NAME = 100;

TaxonomyParser::TaxonomyParser(ActorFactory &actorFactory) : m_actorFactory(actorFactory) {
}

bool TaxonomyParser::_parseLine(const char *fileDir, const char *line) {
	std::cout << fileDir << std::endl;
	bool retValue = true;
	unsigned int raceLevel1HP;
	int result = sscanf(line, "%u\n", &raceLevel1HP);
	if (result != 1) {
		retValue = false;
	}
	else {
		ActorRace* race = new ActorRace(raceLevel1HP);
		m_actorFactory.addActorRaceTaxonomy(race);
	}

	return retValue;
}
