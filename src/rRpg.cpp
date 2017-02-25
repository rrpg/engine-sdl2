#include "rRpg.hpp"

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

}
