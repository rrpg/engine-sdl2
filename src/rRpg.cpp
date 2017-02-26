#include "rRpg.hpp"
#include <SDL2/SDL.h>
#include <iostream>

rRpg::rRpg() : m_hero(Actor()), m_map(Map()) {
	m_map.addActor(&m_hero);
}

rRpg::~rRpg() {
}

void rRpg::loadMap(std::string filePath) {
	E_MapParsingResult res;
	res = m_map.setMap(filePath.c_str());
	if (res != OK) {
		std::cout << "error parsing map: " << res << std::endl;
	}
	m_hero.setX(m_map.getStartPoint().x);
	m_hero.setY(m_map.getStartPoint().y);
}

void rRpg::update() {

}

void rRpg::render() {
	SDL_Rect camera = {
		10, 10, 300, 300
	};
	m_map.render(camera, m_hero.getX(), m_hero.getY());
}
