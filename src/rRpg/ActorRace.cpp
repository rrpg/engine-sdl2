#include <SDL2/SDL.h>
#include <sstream>
#include <string>
#include "ActorRace.hpp"
#include "Actor.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

ActorRace::ActorRace(S_ActorRaceData data) :
	m_data(data)
{
}

std::shared_ptr<Actor> ActorRace::createActor() {
	std::shared_ptr<Actor> actor(std::make_shared<Actor>(*this));
	actor->setHealth((int) m_data.level1HP);
	actor->setMaxHealth(m_data.level1HP);
	actor->setDefence(m_data.level1Defence);
	actor->setAttack(m_data.level1Attack);
	return actor;
}

std::string ActorRace::getTilesetName() {
	if (!m_data.timePerFrame) {
		return m_data.tileset;
	}
	else {
		uint32_t currTime = SDL_GetTicks();
		// the game's animations are of 2frames
		int durationAnimationCycle = m_data.timePerFrame * 2;
		int timeInCycle = (int) currTime % durationAnimationCycle;
		int tilesetIndex = timeInCycle / m_data.timePerFrame;
		std::ostringstream os;
		os << tilesetIndex;
		return m_data.tileset + os.str();
	}
}

int ActorRace::getSpriteX() {
	return m_data.spriteX;
}

int ActorRace::getSpriteY() {
	return m_data.spriteY;
}

void ActorRace::loadTilesetResource() {
	SDL_Renderer* renderer = Game::Instance()->getRenderer();

	if (!m_data.timePerFrame) {
		TextureManager::Instance()->load(m_data.tileset, renderer);
	}
	else {
		TextureManager::Instance()->load(std::string(m_data.tileset) + "0", renderer);
		TextureManager::Instance()->load(std::string(m_data.tileset) + "1", renderer);
	}
}
