#include "ActorFactory.hpp"
#include "Behaviour/Monster.hpp"
#include "GUI/Actor.hpp"
#include <fstream>
#include <libgen.h>

ActorFactory::ActorFactory() :
	m_behaviourFactory(BehaviourFactory()),
	m_graphicFactory(GraphicFactory())
{
}

ActorFactory::~ActorFactory() {
}

bool ActorFactory::parseTaxonomy(const char* taxonomyFile) {
	ResourceManager<S_ActorRaceData> resourceManager;
	if (!resourceManager.setResourceFile(taxonomyFile)) {
		return false;
	}

	resourceManager.parseBinaryFile();
	for (auto raceData : resourceManager.getParsedResources()) {
		ActorRace race(raceData.second);
		race.loadTilesetResource();
		m_mTaxonomy.push_back(race);
	}

	return true;
}

Actor* ActorFactory::createActor(E_ActorRaces race) {
	if ((size_t) race >= m_mTaxonomy.size()) {
		return NULL;
	}

	return m_mTaxonomy[race].createActor();
}

Actor* ActorFactory::createEnemy(E_ActorRaces race) {
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
