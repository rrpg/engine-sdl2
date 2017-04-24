#include "ActorFactory.hpp"
#include "Parser/Taxonomy.hpp"
#include "Behaviour/Monster.hpp"
#include "Graphic/Actor.hpp"
#include <fstream>
#include <libgen.h>

ActorFactory::ActorFactory() :
	m_behaviourFactory(BehaviourFactory()),
	m_graphicFactory(GraphicFactory())
{
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

Actor* ActorFactory::createActor(E_ActorRaces race) {
	if ((size_t) race >= m_mTaxonomy.size()) {
		return NULL;
	}

	return m_mTaxonomy[race]->createActor();
}

Actor* ActorFactory::createRandomFoe() {
	E_ActorRaces race = (E_ActorRaces) (rand() % NB_RACES);
	Actor* actor = createActor(race);
	actor->setBehaviour(m_behaviourFactory.getBehaviour(BEHAVIOUR_MONSTER));
	actor->setGraphic((GraphicActor*) m_graphicFactory.getGraphic(GRAPHIC_ACTOR));
	return actor;
}

Actor* ActorFactory::createHero() {
	Actor* hero = createActor(RACE_HUMAN);
	hero->setBehaviour(m_behaviourFactory.getBehaviour(BEHAVIOUR_PLAYER));
	hero->setGraphic((GraphicActor*) m_graphicFactory.getGraphic(GRAPHIC_PLAYER));
	return hero;
}
