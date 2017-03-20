#include "TaxonomyParser.hpp"
#include "ActorRace.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"
#include <iostream>

const int MAX_CHAR_FILE_PATH = 255;

TaxonomyParser::TaxonomyParser(ActorFactory &actorFactory) : m_actorFactory(actorFactory) {
}

bool TaxonomyParser::_parseLine(const char *line) {
	bool retValue = true;
	char tilesetPath[MAX_CHAR_FILE_PATH];
	unsigned int raceLevel1HP, raceLevel1Defence, raceLevel1Attack, spriteX, spriteY;
	int result = sscanf(
		line,
		"%s %u %u %u %u %u\n",
		tilesetPath, &spriteX, &spriteY,
		&raceLevel1HP, &raceLevel1Defence, &raceLevel1Attack
	);
	if (result != 6) {
		retValue = false;
	}
	else {
		TextureManager::Instance()->load(
			std::string(m_sFileDir) + "/" + tilesetPath,
			tilesetPath,
			Game::Instance()->getRenderer()
		);

		ActorRace* race = new ActorRace(
			raceLevel1HP,
			raceLevel1Defence,
			raceLevel1Attack
		);
		race->setTilesetName(tilesetPath);
		race->setSpriteX(spriteX);
		race->setSpriteY(spriteY);
		m_actorFactory.addActorRaceTaxonomy(race);
	}

	return retValue;
}
