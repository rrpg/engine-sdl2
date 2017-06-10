#include "ActorFactory.hpp"
#include "Behaviour/Monster.hpp"
#include "ResourceManager.hpp"
#include "GUI/Actor.hpp"
#include "Actor.hpp"
#include <fstream>
#include <libgen.h>

ActorFactory::ActorFactory(GraphicFactory &graphicFactory) :
	m_behaviourFactory(BehaviourFactory()),
	m_graphicFactory(graphicFactory)
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

std::shared_ptr<Actor> ActorFactory::createActor(E_ActorRaces race) {
	if ((size_t) race >= m_mTaxonomy.size()) {
		return NULL;
	}

	return m_mTaxonomy[race].createActor();
}

std::shared_ptr<Actor> ActorFactory::createEnemy(E_ActorRaces race) {
	std::shared_ptr<Actor> actor = createActor(race);
	actor->setBehaviour(m_behaviourFactory.getBehaviour(BEHAVIOUR_MONSTER));
	actor->setGraphic((GraphicActor*) m_graphicFactory.getGraphic(GRAPHIC_ACTOR));
	return actor;
}

std::shared_ptr<Actor> ActorFactory::createHero() {
	std::shared_ptr<Actor> hero = createActor(RACE_HUMAN);
	hero->setBehaviour(m_behaviourFactory.getBehaviour(BEHAVIOUR_PLAYER));
	hero->setGraphic((GraphicActor*) m_graphicFactory.getGraphic(GRAPHIC_PLAYER));
	return hero;
}
