#include "Taxonomy.hpp"
#include "Resource.hpp"
#include "../ActorRace.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

TaxonomyParser::TaxonomyParser(ActorFactory &actorFactory) : m_actorFactory(actorFactory) {
}

bool TaxonomyParser::_parseLine(const char *line) {
	bool retValue = true;
	char tileset[ResourceParser::MAX_CHAR_RESOURCE_NAME];
	unsigned int isAnimated,raceLevel1HP, raceLevel1Defence, raceLevel1Attack,
		spriteX, spriteY;
	int result = sscanf(
		line,
		"%s %u %u %u %u %u %u\n",
		tileset, &isAnimated, &spriteX, &spriteY,
		&raceLevel1HP, &raceLevel1Defence, &raceLevel1Attack
	);
	if (result != 7) {
		retValue = false;
	}
	else {
		ActorRace* race = new ActorRace(
			raceLevel1HP,
			raceLevel1Defence,
			raceLevel1Attack
		);
		if (!isAnimated) {
			_addTilesetToRace(race, tileset);
		}
		else {
			_addTilesetToRace(race, std::string(tileset) + "0");
			_addTilesetToRace(race, std::string(tileset) + "1");
		}

		race->setSpriteX(spriteX);
		race->setSpriteY(spriteY);
		m_actorFactory.addActorRaceTaxonomy(race);
	}

	return retValue;
}

void TaxonomyParser::_addTilesetToRace(ActorRace *race, std::string tileset) {
	race->addTilesetName(tileset);
	TextureManager::Instance()->load(
		tileset,
		Game::Instance()->getRenderer()
	);
}
