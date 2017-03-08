#include "TaxonomyParser.hpp"
#include "ActorRace.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"
#include <iostream>

const int MAX_CHAR_FILE_PATH = 255;

TaxonomyParser::TaxonomyParser(ActorFactory &actorFactory) : m_actorFactory(actorFactory) {
}

bool TaxonomyParser::_parseLine(const char *fileDir, const char *line) {
	std::cout << fileDir << std::endl;
	bool retValue = true;
	char tilesetPath[MAX_CHAR_FILE_PATH];
	unsigned int raceLevel1HP, spriteX, spriteY;
	int result = sscanf(
		line,
		"%s %u %u %u\n",
		tilesetPath, &spriteX, &spriteY, &raceLevel1HP
	);
	if (result != 4) {
		retValue = false;
	}
	else {
		std::cout << std::string(fileDir) + "/" + tilesetPath << std::endl;
		TextureManager::Instance()->load(
			std::string(fileDir) + "/" + tilesetPath,
			tilesetPath,
			Game::Instance()->getRenderer()
		);

		ActorRace* race = new ActorRace(raceLevel1HP);
		race->setTilesetName(tilesetPath);
		race->setSpriteX(spriteX);
		race->setSpriteY(spriteY);
		m_actorFactory.addActorRaceTaxonomy(race);
	}

	return retValue;
}
