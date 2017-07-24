#include "rRpg.hpp"
#include "globals.hpp"
#include "FieldOfView.hpp"
#include "HUD.hpp"
#include "Map/Manager.hpp"
#include "Map/Renderer.hpp"
#include "Actor.hpp"
#include "Behaviour/Player.hpp"
#include <iostream>
#include <iterator>
#include "SDL2_framework/Game.h"

rRpg::rRpg() :
	m_hero(nullptr),
	m_graphicFactory(GraphicFactory()),
	m_actorFactory(ActorFactory(m_graphicFactory)),
	m_map(Map()),
	m_mapRenderer(MapRenderer(m_map, m_graphicFactory))
{
	m_camera = {
		0, 0,
		Game::Instance()->getScreenWidth(), Game::Instance()->getScreenHeight()
	};

	m_mapRenderer.setCamera(m_camera);
}

rRpg::~rRpg() {}

Map &rRpg::getMap() {
	return m_map;
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

bool rRpg::loadInitialMap() {
	return loadMap("start", 0);
}

bool rRpg::loadStartMap() {
	std::string mapFile = std::string(GAME_START_MAP) + "-0";
	S_MapSpecs specs;
	strncpy(specs.name, GAME_START_MAP, MAX_LENGTH_MAP_NAME);
	specs.level = 0;
	specs.type = CAVE;
	specs.width = 20;
	specs.height = 20;
	specs.hasEnemies = false;
	return _loadMap(mapFile, specs);
}

bool rRpg::loadMap(std::string mapName, int level) {
	std::string mapFile = m_map.getKeyName(mapName, level);
	S_MapSpecs specs;
	strncpy(specs.name, mapName.c_str(), MAX_LENGTH_MAP_NAME);
	specs.level = level;
	specs.type = CAVE;
	specs.width = 50;
	specs.height = 50;
	specs.hasEnemies = true;
	return _loadMap(mapFile, specs);
}

bool rRpg::_loadMap(std::string mapFile, S_MapSpecs specs) {
	MapManager manager;
	std::string prevMapKey = m_map.getKeyName();
	if (manager.mapExists(mapFile)) {
		if (!manager.loadMap(m_map, mapFile)) {
			return false;
		}
	}
	else if (!manager.generateMap(m_map, mapFile, specs)) {
		return false;
	}

	int x, y;
	t_coordinates *startPoint = m_map.getMapJunction(prevMapKey);
	if (startPoint == NULL) {
		x = (int) m_map.getStartPoint().getX();
		y = (int) m_map.getStartPoint().getY();
	}
	else {
		x = startPoint->first;
		y = startPoint->second;
	}

	m_map.initEnemies(m_actorFactory);
	m_map.setTileFile(m_sTilesFile.c_str());
	m_map.setObjectsFile(m_sObjectsFile.c_str());
	m_hero->setX(x);
	m_hero->setY(y);
	m_map.addActor(m_hero);
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
	std::unordered_map<std::string, std::shared_ptr<Actor>> actors = m_map.getActors();
	unblock();

	m_hero->update(this);
	for (auto it = actors.begin(); it != actors.end(); ++it) {
		if (it->second != m_hero) {
			it->second->update(this);
		}
	}

	if (!m_hero->isDead()) {
		m_map.clearDeadActors();
	}
}

void rRpg::render() {
	FieldOfView fov;
	fov.calculate(m_map, m_hero);
	t_coordinates center = {m_hero->getX(), m_hero->getY()};
	m_mapRenderer.render(
		fov.getVisible(),
		center
	);
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
