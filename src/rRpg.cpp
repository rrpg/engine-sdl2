#include "rRpg.hpp"

rRpg::rRpg() : m_hero(Actor()), m_map(Map()) {
	m_map.addActor(&m_hero);
}

rRpg::~rRpg() {
}

void rRpg::update() {

}

void rRpg::render() {

}
