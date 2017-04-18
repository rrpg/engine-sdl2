#ifndef __ACTOR_RACE__
#define __ACTOR_RACE__

#include "Actor.hpp"
#include <string>
#include <vector>

class ActorRace {
	private:
	unsigned int m_iLevel1HP;
	unsigned int m_iLevel1Defence;
	unsigned int m_iLevel1Attack;
	std::vector<std::string> m_vTilesetNames = {};
	unsigned int m_iSpriteX = 0;
	unsigned int m_iSpriteY = 0;

	public:
	ActorRace(unsigned int level1HP, unsigned int level1Defence, unsigned int level1Attack);
	Actor* createActor();
	void addTilesetName(std::string name);
	void setSpriteX(unsigned int spriteX);
	void setSpriteY(unsigned int spriteY);
	std::string getTilesetName();
	unsigned int getSpriteX();
	unsigned int getSpriteY();
};

#endif
