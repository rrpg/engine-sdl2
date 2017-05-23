#ifndef __ACTOR_RACE__
#define __ACTOR_RACE__

#include "Actor.hpp"
#include "types.hpp"
#include <string>
#include <vector>

class ActorRace {
	private:
	S_ActorRaceData m_data;

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
