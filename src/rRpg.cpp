#include "rRpg.hpp"

rRpg::rRpg() : m_hero(Actor()), m_map(Map()) {
	m_map.addActor(&m_hero);
}

void rRpg::update() {

}

void rRpg::render() {

}
