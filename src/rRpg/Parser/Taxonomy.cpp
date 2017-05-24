#include "Taxonomy.hpp"
#include "types.hpp"
#include "../ActorRace.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

TaxonomyParser::TaxonomyParser(ActorFactory &actorFactory) : m_actorFactory(actorFactory) {
}

bool TaxonomyParser::_parseLine(const char *line) {
	bool retValue = true;
	S_ActorRaceData raceData;
	int result = sscanf(
		line,
		"%s %d %d %d %d %d %d\n",
		raceData.tileset,
		&raceData.timePerFrame,
		&raceData.spriteX,
		&raceData.spriteY,
		&raceData.level1HP,
		&raceData.level1Defence,
		&raceData.level1Attack
	);
	if (result != 7) {
		retValue = false;
	}
	else {
		_loadTilesetTexture(raceData);

		ActorRace* race = new ActorRace(raceData);
		m_actorFactory.addActorRaceTaxonomy(race);
	}

	return retValue;
}

void TaxonomyParser::_loadTilesetTexture(S_ActorRaceData &race) {
	SDL_Renderer* renderer = Game::Instance()->getRenderer();

	if (!race.timePerFrame) {
		TextureManager::Instance()->load(race.tileset, renderer);
	}
	else {
		TextureManager::Instance()->load(std::string(race.tileset) + "0", renderer);
		TextureManager::Instance()->load(std::string(race.tileset) + "1", renderer);
	}
}
