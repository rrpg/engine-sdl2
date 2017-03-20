#include "Taxonomy.hpp"
#include "Resource.hpp"
#include "../ActorRace.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"
#include <iostream>

TaxonomyParser::TaxonomyParser(ActorFactory &actorFactory) : m_actorFactory(actorFactory) {
}

bool TaxonomyParser::_parseLine(const char *line) {
	bool retValue = true;
	char tileset[ResourceParser::MAX_CHAR_RESOURCE_NAME];
	unsigned int raceLevel1HP, raceLevel1Defence, raceLevel1Attack, spriteX, spriteY;
	int result = sscanf(
		line,
		"%s %u %u %u %u %u\n",
		tileset, &spriteX, &spriteY,
		&raceLevel1HP, &raceLevel1Defence, &raceLevel1Attack
	);
	if (result != 6) {
		retValue = false;
	}
	else {
		TextureManager::Instance()->load(
			tileset,
			Game::Instance()->getRenderer()
		);

		ActorRace* race = new ActorRace(
			raceLevel1HP,
			raceLevel1Defence,
			raceLevel1Attack
		);
		race->setTilesetName(tileset);
		race->setSpriteX(spriteX);
		race->setSpriteY(spriteY);
		m_actorFactory.addActorRaceTaxonomy(race);
	}

	return retValue;
}
