#include "rRpg.hpp"

rRpg::rRpg() : m_hero(Actor()), m_vActors({}) {
	m_vActors.push_back(&m_hero);
}
