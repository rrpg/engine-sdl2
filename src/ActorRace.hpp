#ifndef __ACTOR_RACE__
#define __ACTOR_RACE__

#include "Actor.hpp"
#include <string>

class ActorRace {
	private:
	unsigned int m_iLevel1HP;
	std::string m_sTilesetName = "";
	unsigned int m_iSpriteX = 0;
	unsigned int m_iSpriteY = 0;

	public:
	ActorRace(unsigned int level1HP);
	Actor* createActor();
	void setTilesetName(std::string name);
	void setSpriteX(unsigned int spriteX);
	void setSpriteY(unsigned int spriteY);
	std::string getTilesetName();
	unsigned int getSpriteX();
	unsigned int getSpriteY();
};

#endif
