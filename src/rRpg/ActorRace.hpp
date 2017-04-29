#ifndef __ACTOR_RACE__
#define __ACTOR_RACE__

#include "Actor.hpp"
#include <string>
#include <vector>

class ActorRace {
	private:
	int m_iLevel1HP;
	int m_iLevel1Defence;
	int m_iLevel1Attack;
	std::vector<std::string> m_vTilesetNames = {};
	int m_iTimePerFrame = 0;
	int m_iSpriteX = 0;
	int m_iSpriteY = 0;

	public:
	ActorRace(int level1HP, int level1Defence, int level1Attack);
	Actor* createActor();
	void addTilesetName(std::string name);
	void setTimePerFrame(int timePerFrame);
	void setSpriteX(int spriteX);
	void setSpriteY(int spriteY);
	std::string getTilesetName();
	int getSpriteX();
	int getSpriteY();
};

#endif
