#include "rRpg.hpp"
#include "MapGenerator.hpp"
#include "Behaviour/Player.hpp"
#include "Parser/Map.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <iterator>
#include "SDL2_framework/Game.h"

rRpg::rRpg() : m_hero(0), m_actorFactory(ActorFactory()), m_map(Map()) {
}

rRpg::rRpg(const rRpg &r) : m_actorFactory(ActorFactory()), m_map(Map()) {
	m_hero = r.m_hero;
	m_map = r.m_map;
	m_actorFactory = r.m_actorFactory;
}

rRpg & rRpg::operator=(const rRpg &r) {
	// check for "self assignment" and do nothing in that case
	if (this == &r) {
		return *this;
	}

	m_hero = r.m_hero;
	m_map = r.m_map;
	return *this;
}

rRpg::~rRpg() {
}

Map &rRpg::getMap() {
	return m_map;
}

Actor *rRpg::getHero() {
	return m_hero;
}

bool rRpg::loadMap(std::string filePath, std::string tilesFilePath) {
	FILE *f = 0;
	MapParser parser = MapParser();
	// generate the map if it does not exist
	f = fopen(filePath.c_str(), "r");
	if (f) {
		fclose(f);
	}
	else {
		MapGenerator generator = MapGenerator();
		Map map = generator.generate(CAVE, 50, 50);
		parser.setMap(&map);
		parser.saveMap(filePath.c_str());
	}

	// load it
	E_FileParsingResult res;
	parser.setMap(&m_map);
	res = parser.parseFile(filePath.c_str());
	bool ret = true;
	if (res != OK) {
		std::cout << "error parsing map: " << res << std::endl;
		ret = false;
	}

	m_map.initEnemies(m_actorFactory);
	m_map.setTileFile(tilesFilePath.c_str());
	return ret;
}

bool rRpg::loadTaxonomy(std::string filePath) {
	E_FileParsingResult res;
	res = m_actorFactory.parseTaxonomy(filePath.c_str());
	std::cout << "Taxonomy parsed\n";
	bool ret = true;
	if (res != OK) {
		std::cout << "error parsing taxonomy: " << res << std::endl;
		ret = false;
	}

	return ret;
}

void rRpg::initialiseHero() {
	m_hero = m_actorFactory.createHero();
	m_hero->setX((int) m_map.getStartPoint().getX());
	m_hero->setY((int) m_map.getStartPoint().getY());
	m_map.addActor(m_hero);
}

void rRpg::update() {
	std::unordered_map<std::string, Actor*> actors = m_map.getActors();
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
	SDL_Rect camera = {
		0, 0,
		Game::Instance()->getScreenWidth(), Game::Instance()->getScreenHeight()
	};
	m_map.render(camera, m_hero->getX(), m_hero->getY());
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
