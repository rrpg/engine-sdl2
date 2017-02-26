#include "rRpg.hpp"
#include <SDL2/SDL.h>

rRpg::rRpg() : m_hero(Actor()), m_map(Map()) {
	m_map.addActor(&m_hero);
}

rRpg::~rRpg() {
}

void rRpg::loadMap(std::string filePath) {
	m_map.setMap(filePath.c_str());
}

void rRpg::update() {

}

void rRpg::render() {
	SDL_Rect camera = {
		10, 10, 300, 300
	};
	int center = 180;
	m_map.render(camera, center);
}
