#include "rRpg.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2_framework/Game.h"

rRpg::rRpg() : m_hero(Actor()), m_map(Map()) {
}

rRpg::~rRpg() {
}

Actor* rRpg::getHero() {
	return &m_hero;
}

Map* rRpg::getMap() {
	return &m_map;
}

void rRpg::loadMap(std::string filePath) {
	E_MapParsingResult res;
	res = m_map.setMap(filePath.c_str());
	if (res != OK) {
		std::cout << "error parsing map: " << res << std::endl;
	}
	m_hero.setX((int) m_map.getStartPoint().getX());
	m_hero.setY((int) m_map.getStartPoint().getY());
	// @TODO Move this somewhere else
	m_hero.setTilesetRowIndex(1);
	m_map.addActor(&m_hero);
}

void rRpg::render() {
	SDL_Rect camera = {
		0, 0,
		Game::Instance()->getScreenWidth(), Game::Instance()->getScreenHeight()
	};
	m_map.render(camera, m_hero.getX(), m_hero.getY());
}
