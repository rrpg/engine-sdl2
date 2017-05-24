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
		S_ActorRaceData raceData;
		raceData.level1HP = raceLevel1HP;
		raceData.level1Defence = raceLevel1Defence;
		raceData.level1Attack = raceLevel1Attack;
		raceData.timePerFrame = timePerFrame;
		raceData.spriteX = spriteX;
		raceData.spriteY = spriteY;
		_addTilesetToRace(raceData, tileset);

		ActorRace* race = new ActorRace(raceData);
		m_actorFactory.addActorRaceTaxonomy(race);
	}

	return retValue;
}

void TaxonomyParser::_addTilesetToRace(S_ActorRaceData &race, std::string tileset) {
	race.tileset = tileset;
	SDL_Renderer* renderer = Game::Instance()->getRenderer();

	if (!race.timePerFrame) {
		TextureManager::Instance()->load(tileset, renderer);
	}
	else {
		TextureManager::Instance()->load(std::string(tileset) + "0", renderer);
		TextureManager::Instance()->load(std::string(tileset) + "1", renderer);
	}
}
