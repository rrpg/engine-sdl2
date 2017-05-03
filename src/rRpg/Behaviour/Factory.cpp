#include "Behaviour/Factory.hpp"
#include "Behaviour/Player.hpp"
#include "Behaviour/Monster.hpp"

BehaviourFactory::BehaviourFactory() {
	m_vBehaviours = {
		new BehaviourPlayer(),
		new BehaviourMonster()
	};
}

BehaviourFactory::~BehaviourFactory() {
	for (auto behaviour : m_vBehaviours) {
		delete behaviour;
	}
}

Behaviour *BehaviourFactory::getBehaviour(E_Behaviours behaviour) {
	return m_vBehaviours[behaviour];
}
