#include "ActorFactory.hpp"
#include "TaxonomyParser.hpp"
#include <fstream>
#include <libgen.h>

const int MAX_CHARS_PER_LINE = 1024;

ActorFactory::ActorFactory() {
}

ActorFactory::~ActorFactory() {
	for (auto race : m_mTaxonomy) {
		free(race);
	}
}

E_FileParsingResult ActorFactory::parseTaxonomy(const char* taxonomyFile) {
	TaxonomyParser parser = TaxonomyParser(*this);
	E_FileParsingResult result = parser.parseFile(taxonomyFile);
	return result;
}

void ActorFactory::addActorRaceTaxonomy(ActorRace* race) {
	m_mTaxonomy.push_back(race);
}
