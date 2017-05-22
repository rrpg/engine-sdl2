#include "Taxonomy.hpp"
#include "types.hpp"
#include "../ActorRace.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

TaxonomyParser::TaxonomyParser(ActorFactory &actorFactory) : m_actorFactory(actorFactory) {
}

bool TaxonomyParser::_parseLine(const char *line) {
	bool retValue = true;
	char tileset[MAX_LENGTH_TILESET_NAME];
	int timePerFrame,raceLevel1HP, raceLevel1Defence, raceLevel1Attack,
		spriteX, spriteY;
	int result = sscanf(
		line,
		"%s %d %d %d %d %d %d\n",
		tileset, &timePerFrame, &spriteX, &spriteY,
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
		if (!timePerFrame) {
			_addTilesetToRace(race, tileset);
		}
		else {
			race->setTimePerFrame(timePerFrame);
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
