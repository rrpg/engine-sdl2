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
	ActorRace(S_ActorRaceData data);
	Actor* createActor();
	void addTilesetName(std::string name);
	std::string getTilesetName();
	int getSpriteX();
	int getSpriteY();
};

#endif
