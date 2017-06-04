#include "rRpg.hpp"
#include "HUD.hpp"
#include "MapManager.hpp"
#include "Behaviour/Player.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <iterator>
#include "SDL2_framework/Game.h"

rRpg::rRpg() :
	m_hero(nullptr),
	m_actorFactory(ActorFactory()),
	m_mapManager(MapManager())
{
}

rRpg::~rRpg() {}

Map &rRpg::getMap() {
	return m_mapManager.getMap();
}

std::shared_ptr<Actor> rRpg::getHero() {
	return m_hero;
}

void rRpg::setTilesFile(std::string tilesFilePath) {
	m_sTilesFile = tilesFilePath;
}

void rRpg::setObjectsFile(std::string objectsFilePath) {
	m_sObjectsFile = objectsFilePath;
}

bool rRpg::loadMap(std::string mapName, int level) {
	if (!m_mapManager.loadMap(mapName, level)) {
		return false;
	}

	m_mapManager.getMap().initEnemies(m_actorFactory);
	m_mapManager.getMap().setTileFile(m_sTilesFile.c_str());
	m_mapManager.getMap().setObjectsFile(m_sObjectsFile.c_str());
	m_hero->setX((int) m_mapManager.getMap().getStartPoint().getX());
	m_hero->setY((int) m_mapManager.getMap().getStartPoint().getY());
	m_mapManager.getMap().addActor(m_hero);
	return true;
}

bool rRpg::loadTaxonomy(std::string filePath) {
	bool ret = true;
	if (m_actorFactory.parseTaxonomy(filePath.c_str())) {
		std::cout << "Taxonomy parsed\n";
	}
	else {
		std::cout << "error parsing taxonomy" << std::endl;
		ret = false;
	}

	return ret;
}

void rRpg::initialiseHero() {
	m_hero = m_actorFactory.createHero();
}

void rRpg::update() {
	std::unordered_map<std::string, std::shared_ptr<Actor>> actors = m_mapManager.getMap().getActors();
	unblock();

	m_hero->update(this);
	for (auto it = actors.begin(); it != actors.end(); ++it) {
		if (it->second != m_hero) {
			it->second->update(this);
		}
	}

	if (!m_hero->isDead()) {
		m_mapManager.getMap().clearDeadActors();
	}
}

void rRpg::render() {
	SDL_Rect camera = {
		0, 0,
		Game::Instance()->getScreenWidth(), Game::Instance()->getScreenHeight()
	};
	m_mapManager.getMap().render(camera, m_hero->getX(), m_hero->getY());
	// render HUD
	HUD::render(Game::Instance(), m_hero);
}

bool rRpg::isBlocked() {
	return m_bIsBlocked;
}

void rRpg::block() {
	m_bIsBlocked = true;
}

void rRpg::unblock() {
	m_bIsBlocked = false;
}
