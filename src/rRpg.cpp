#include "rRpg.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2_framework/ServiceProvider.h"
#include "SDL2_framework/UserActions.h"

rRpg::rRpg() : m_hero(Actor()), m_map(Map()) {
}

rRpg::~rRpg() {
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

void rRpg::update() {
	UserActions* userActions = ServiceProvider::getUserActions();
	if (userActions->getActionState("MOVE_PLAYER_UP")) {
		m_hero.setY(m_hero.getY() - 1);
	}
	else if (userActions->getActionState("MOVE_PLAYER_DOWN")) {
		m_hero.setY(m_hero.getY() + 1);
	}
	else if (userActions->getActionState("MOVE_PLAYER_LEFT")) {
		m_hero.setX(m_hero.getX() - 1);
	}
	else if (userActions->getActionState("MOVE_PLAYER_RIGHT")) {
		m_hero.setX(m_hero.getX() + 1);
	}
}

void rRpg::render() {
	SDL_Rect camera = {
		10, 10, 300, 300
	};
	m_map.render(camera, m_hero.getX(), m_hero.getY());
}
