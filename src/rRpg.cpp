#include "rRpg.hpp"

rRpg::rRpg() : m_hero(Actor()), m_map(Map()) {
	m_map.addActor(&m_hero);
}

rRpg::~rRpg() {
	m_map.clean();
}

void rRpg::update() {

}

void rRpg::render() {

}
