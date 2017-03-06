#include "rRpg.hpp"
#include "BehaviourPlayer.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <iterator>
#include "SDL2_framework/Game.h"

rRpg::rRpg() : m_hero(Actor()), m_map(Map()) {
}

rRpg::~rRpg() {
}

Map* rRpg::getMap() {
	return &m_map;
}

void rRpg::loadMap(std::string filePath) {
	E_FileParsingResult res;
	res = m_map.setMap(filePath.c_str());
	if (res != OK) {
		std::cout << "error parsing map: " << res << std::endl;
		return;
	}
	m_hero.setX((int) m_map.getStartPoint().getX());
	m_hero.setY((int) m_map.getStartPoint().getY());
	// @TODO Move this somewhere else
	m_hero.setTilesetRowIndex(1);
	m_hero.setBehaviour(new BehaviourPlayer());
	m_hero.startTurn();
	m_map.addActor(&m_hero);
}

void rRpg::update() {
	std::unordered_map<std::string, Actor*> actors = m_map.getActors();
	std::unordered_map<std::string, Actor*>::iterator nextActor;
	for (std::unordered_map<std::string, Actor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
		it->second->update(this);
		if (it->second->isTurn() && it->second->playedTurn()) {
			it->second->endTurn();
			nextActor = std::next(it, 1);
			if (nextActor == actors.end()) {
				nextActor = actors.begin();
			}

			nextActor->second->startTurn();
		}
	}
}

void rRpg::render() {
	SDL_Rect camera = {
		0, 0,
		Game::Instance()->getScreenWidth(), Game::Instance()->getScreenHeight()
	};
	m_map.render(camera, m_hero.getX(), m_hero.getY());
}
